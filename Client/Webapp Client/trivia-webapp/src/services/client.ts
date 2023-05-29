import { useEffect, useContext} from "react";
import { AuthContext } from "../App";
import { RoomListContext } from "../contexts/RoomListContext";
import { CurrentRoomDataContext } from "../contexts/CurrentRoomDataContext";
import { useNavigate } from "react-router-dom";
import { ResponseContext } from "../contexts/ResponseContext";
import WebSocketContext from "../contexts/WebSocketContext";
import { SelectedRoomIdContext } from "../contexts/SelectedRoomContext";
import { HighscoresContext } from "../contexts/HighscoresContext";
import { PersonalStatisticsContext } from "../contexts/PersonalStatisticsContext";
import {
  LoginRequest,
  SignupRequest,
  GetPlayersInRoomRequest,
  JoinRoomRequest,
  CreateRoomRequest,
  ParsedResponse,
  Rooms
} from "../utils/types";
import { RoomData } from "../utils/types";

const SERVER_URL = "ws://127.0.0.1:9696";
const RequestCodes = {
  LoginRequestCode: 1,
  SignupRequestCode: 2,
  LogoutRequestCode: 3,
  JoinRoomRequestCode: 4,
  GetRoomsRequestCode: 5,
  GetPlayersInRoomRequestCode: 6,
  CreateRoomRequestCode: 7,
  GetHighScoreRequestCode: 8,
  GetPersonalStatsRequestCode: 9,
};

const ResponseCodes = {
  ErrorResponseCode: 0,
  LoginResponseCode: 1,
  SignupResponseCode: 2,
  LogoutResponseCode: 3,
  JoinRoomResponseCode: 4,
  GetRoomsResponseCode: 5,
  GetPlayersInRoomResponseCode: 6,
  CreateRoomResponseCode: 7,
  GetHighScoreResponseCode: 8,
  GetPersonalStatsResponseCode: 9,
};

const useClient = () => {
  const { socket, setSocket, connectionEstablished } = useContext(WebSocketContext);
  const navigate = useNavigate();
  const { setResponseMessage } = useContext(ResponseContext);
  const { setIsLoggedIn } = useContext(AuthContext);
  const { setConnectedUsers } = useContext(CurrentRoomDataContext);
  const { setSelectedRoomId } = useContext(SelectedRoomIdContext);
  const { setRoomList } = useContext(RoomListContext);
  const { setHighscores } = useContext(HighscoresContext);
  const { personalStatistics, setPersonalStatistics } = useContext(PersonalStatisticsContext);
  
  useEffect(() => {
    if (!socket || !connectionEstablished)
    {
      console.log("Error in connection");
      return;
    }
    // Set binaryType to 'arraybuffer' to receive data in binary format
    socket.binaryType = "arraybuffer";

    socket.onmessage = (event) => {
      //console.log(event.data);
      // Parse the server response
      console.log(event.data);
      const response = new Uint8Array(event.data);
      const parsedResponse = parseServerResponse(response);

      // Extract the response code and data from the parsed response
      const { responseCode, data } = parsedResponse;
      console.log("Response code: ", responseCode);

      //Use a switch statement to handle the response differently based on the response code
      switch (responseCode) {
        case ResponseCodes.ErrorResponseCode:
          data["message"] ? setResponseMessage(data["message"]) : console.log(data["message"]);
          console.log(data["message"]);
          break;
        case ResponseCodes.LoginResponseCode:
          console.log("User is now logged in");
          setResponseMessage("");
          setIsLoggedIn(true);
          navigate("/main-menu");
          break;
        case ResponseCodes.SignupResponseCode:
          console.log("Signup successful");
          break;
        case ResponseCodes.LogoutResponseCode:
          setIsLoggedIn(false);
          navigate("/login");
          console.log("Logged out");
          break;
        case ResponseCodes.GetRoomsResponseCode:
          if(!data["Rooms"] || data["Rooms"].length === 0)
          {
            console.log(data);
            return;
          }
          const updatedRoomsData: Map<number, RoomData> = new Map();

          data["Rooms"].forEach((item: any, index: number) => {
            updatedRoomsData.set(index, {
              roomId: index,
              roomName: item.name,
              maxUsers: item.maxPlayers,
              questionCount: item.numOfQuestionsInGame,
              answerTimeout: item.timePerQuestion,
              isActive: item.isActive
            });
          });

          const updatedRoomList: Rooms = {
            rooms: updatedRoomsData
          };
          console.log(updatedRoomList);
          setRoomList(updatedRoomList);
          break;
        case ResponseCodes.GetPlayersInRoomResponseCode:
          if(!data["PlayersInRoom"]) return;
          const connectedUsers: string[] = data["PlayersInRoom"].split(", ");
          setConnectedUsers(connectedUsers);
          console.log(data);
          break;
        case ResponseCodes.CreateRoomResponseCode:
          console.log("Created room with the id: " + data["roomId"]);
          //if(!data["roomId"]) return;
          navigate("/room-list/room");
          setSelectedRoomId(data["roomId"])
          break;
        case ResponseCodes.JoinRoomResponseCode:
            navigate("/room-list/room");
          break;
        case ResponseCodes.GetHighScoreResponseCode:
          data["HighScores"] ? setHighscores(data["HighScores"]) : console.log(data["HighScores"]);  
          console.log(data);
          break;
        case ResponseCodes.GetPersonalStatsResponseCode:
          data["UserStatistics"] ? setPersonalStatistics(data["UserStatistics"]) : console.log(data["UserStatistics"]);    
          console.log(personalStatistics);
          break;
        //Handle unknown response code
        default:
          console.log("Unknown response code");
          break;
      }
    };
  }, []);

  const sendDataToServer = (requestCode: number, data: any) => {
    // Check if the WebSocket connection has been established
    if(!socket)
    {
      const newSocket = new WebSocket(SERVER_URL);
      setSocket(newSocket);
    }
    
    if (socket && connectionEstablished) {
      // Convert the request code to a binary format (Uint8Array)
      const codeBytes = new Uint8Array([requestCode]);

      // Convert the data to a JSON string, and then to a binary format
      const dataString = JSON.stringify(data);
      const dataBytes = new TextEncoder().encode(dataString);

      // Calculate the length of the data in binary format and store it in a Uint8Array.
      // The length is represented as a 32-bit integer, split into four 8-bit parts.
      const lengthBytes = new Uint8Array([
        (dataBytes.length >> 24) & 0xff, // Get the first 8 bits of the length
        (dataBytes.length >> 16) & 0xff, // Get the next 8 bits of the length
        (dataBytes.length >> 8) & 0xff, // Get the next 8 bits of the length
        dataBytes.length & 0xff, // Get the last 8 bits of the length
      ]);

      // Prepare the final payload to be sent
      // The payload will contain the code, the length, and the data itself
      const payload = new Uint8Array(
        codeBytes.length + lengthBytes.length + dataBytes.length
      );

      // Set the request code in the payload
      payload.set(codeBytes);

      // Set the length in the payload, after the request code
      payload.set(lengthBytes, codeBytes.length);

      // Set the data in the payload, after the request code and the length
      payload.set(dataBytes, codeBytes.length + lengthBytes.length);

      // Finally, send the payload over the WebSocket connection
      socket.send(payload.buffer);

      console.log("Buffer" + payload.buffer);
    }
  };

  const parseServerResponse = (response: Uint8Array): ParsedResponse => {
    const responseCode: number = response[0];
    const dataLengthBytes: Uint8Array = response.slice(1, 5);
    console.log(response);
    const dataLength: number =
      (dataLengthBytes[3] << 24) +
      (dataLengthBytes[2] << 16) +
      (dataLengthBytes[1] << 8) +
      dataLengthBytes[0];
    const jsonData: string = new TextDecoder().decode(
      response.slice(5, 5 + dataLength)
    );

    const parsedResponse: ParsedResponse = {
      responseCode,
      data: JSON.parse(jsonData),
    };

    return parsedResponse;
  };

  const login = (request: LoginRequest) => {
    sendDataToServer(RequestCodes.LoginRequestCode, request);
  };

  const signup = (request: SignupRequest) => {
    sendDataToServer(RequestCodes.SignupRequestCode, request);
  };

  const logout = () => {
    sendDataToServer(RequestCodes.LogoutRequestCode, {});
  };

  const joinRoom = (request: JoinRoomRequest) => {
    console.log("Joining room with the id: " + request.roomId);
    setSelectedRoomId(request.roomId);
    sendDataToServer(RequestCodes.JoinRoomRequestCode, request);
  };

  const createRoom = (request: CreateRoomRequest) => {
    sendDataToServer(RequestCodes.CreateRoomRequestCode, request);
  };

  const getPlayersInRoom = (request: GetPlayersInRoomRequest) => {
    sendDataToServer(RequestCodes.GetPlayersInRoomRequestCode, request);
  };

  const getRooms = () => {
    sendDataToServer(RequestCodes.GetRoomsRequestCode, {});
  };

  return { login, signup, logout, joinRoom, createRoom, getPlayersInRoom, getRooms };
  const getHighscores = () => {
    sendDataToServer(RequestCodes.GetHighScoreRequestCode, {});
  }

  const getPersonalStatistics = () => {
    sendDataToServer(RequestCodes.GetPersonalStatsRequestCode, {});
  }

  return { login, signup, logout, joinRoom, createRoom, getHighscores, getPersonalStatistics, getPlayersInRoom, getRooms};
};

export default useClient;
