import { useEffect, useContext } from "react";
import { useAuth, useResponse, useWebSocket, useSelectedRoomId, useCurrentRoomData, useCurrentRoomState, usePersonalStatistics, useRoomList, useHighscores, useUser } from "../contexts/CustomHooks";
import { useNavigate } from "react-router-dom";
import {
  LoginRequest,
  SignupRequest,
  GetPlayersInRoomRequest,
  JoinRoomRequest,
  CreateRoomRequest,
  SubmitAnswerRequest,
  ParsedResponse,
  Rooms,
  RoomState,
  RoomData
} from "../utils/types";

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
  CloseRoomRequestCode: 10,
  StartGameRequestCode: 11,
  GetRoomStateRequestCode: 12,
  LeaveRoomRequestCode: 13,
  GetGameResultsRequestCode: 14,
  SubmitAnswerRequestCode: 15,
  GetQuestionRequestCode: 16,
  LeaveGameRequestCode: 17
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
  CloseRoomResponseCode: 10,
  StartGameResponseCode: 11,
  GetRoomStateResponseCode: 12,
  LeaveRoomResponseCode: 13,
  GetGameResultsResponseCode: 14,
  SubmitAnswerResponseCode: 15,
  GetQuestionResponseCode: 16,
  LeaveGameResponseCode: 17
};

let username: string;
let newRoomData: RoomData;
let joinedRoomId: number;


const useClient = () => {
  const { socket, setSocket, connectionEstablished } = useWebSocket();
  const navigate = useNavigate();
  const { setResponseMessage } = useResponse();
  const { setIsLoggedIn } = useAuth();
  const { setSelectedRoomId } = useSelectedRoomId();
  const { setRoomList } = useRoomList();
  const { setHighscores } = useHighscores();
  const { setPersonalStatistics } = usePersonalStatistics();
  const { setCurrentRoomState } = useCurrentRoomState();
  const { setCurrentRoomData } = useCurrentRoomData();
  const { setIsInRoom, setUsername } = useUser();
  
  useEffect(() => {
    if (!socket || !connectionEstablished)
    {
      console.log("Error in connection");
      return;
    }
    // Set binaryType to 'arraybuffer' to receive data in binary format
    socket.binaryType = "arraybuffer";

    socket.onmessage = (event) => {
      // Parse the server response
      const response = new Uint8Array(event.data);
      const parsedResponse = parseServerResponse(response);

      // Extract the response code and data from the parsed response
      const { responseCode, data } = parsedResponse;
      //Use a switch statement to handle the response differently based on the response code
      switch (responseCode) {
        case ResponseCodes.ErrorResponseCode:
          if(data["message"])
          {
            if(data["message"] === "The user isn't in any room!")
            {
              setRoomList(null);
              setIsInRoom(false);
              navigate("/rooms/list");
              return;
            }
            setResponseMessage(data["message"])
          }
          break;
        case ResponseCodes.LoginResponseCode:
          setResponseMessage("");
          setIsLoggedIn(true);
          setUsername(username);
          break;
        case ResponseCodes.SignupResponseCode:
          break;
        case ResponseCodes.LogoutResponseCode:
          setIsLoggedIn(false);
          setIsInRoom(false);
          break;
        case ResponseCodes.GetRoomsResponseCode:
          if(!data["Rooms"] || data["Rooms"].length === 0)
          {
            setRoomList(null);
            return;
          }

          const updatedRoomsData: Map<number, RoomData> = new Map();
          Object.entries(data["Rooms"]).forEach(([index, item]: [string, any]) => {
            const numericRoomId = Number(item.roomId);
            updatedRoomsData.set(numericRoomId, {
                roomId: numericRoomId,
                roomName: item.name,
                maxUsers: item.maxPlayers,
                questionCount: item.numOfQuestionsInGame,
                answerTimeout: item.timePerQuestion,
                isActive: item.isActive,
                category: item.category
            });
        });
          const updatedRoomList: Rooms = {
            rooms: updatedRoomsData
          };
          setRoomList(updatedRoomList);
          break;
        case ResponseCodes.CreateRoomResponseCode:
          setSelectedRoomId(data["roomId"]);
          newRoomData.roomId = Number(data["roomId"]);
          console.log("Setting room data");
          setCurrentRoomData(newRoomData);
          setIsInRoom(true);
          break;
        case ResponseCodes.JoinRoomResponseCode:
            setIsInRoom(true);
            navigate("/rooms/" + joinedRoomId);
          break;
        case ResponseCodes.GetHighScoreResponseCode:
          if(data["Highscores"]) setHighscores(data["HighScores"])
          break;
        case ResponseCodes.GetPersonalStatsResponseCode:
          if(data["UserStatistics"]) setPersonalStatistics(data["UserStatistics"])  
          break;
        case ResponseCodes.CloseRoomResponseCode:
          setCurrentRoomData(null);
          //setIsInRoom(false);
          
          break;
        case ResponseCodes.StartGameResponseCode:
          //Start game
          console.log("Game started");
          break;
        case ResponseCodes.GetRoomStateResponseCode:
          const updatedRoomState: RoomState = {
            hasGameBegan: data["hasGameBegun"],
            players: data["players"],
            questionCount: data["questionCount"],
            answerTimeout: data["answerTimeOut"]
          }
          setCurrentRoomState(updatedRoomState);
          break;
        case ResponseCodes.LeaveRoomResponseCode:
          setIsInRoom(false);
          navigate("/rooms/list");
          break;
        case ResponseCodes.GetGameResultsResponseCode:
          break;
        case ResponseCodes.SubmitAnswerResponseCode:
          break;
        case ResponseCodes.GetQuestionResponseCode:
          break;
        case ResponseCodes.LeaveGameResponseCode:
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
    }
  };

  const parseServerResponse = (response: Uint8Array): ParsedResponse => {
    const responseCode: number = response[0];
    const dataLengthBytes: Uint8Array = response.slice(1, 5);
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
    username = request.username;
    sendDataToServer(RequestCodes.LoginRequestCode, request);
  };

  const signup = (request: SignupRequest) => {
    sendDataToServer(RequestCodes.SignupRequestCode, request);
  };

  const logout = () => {
    sendDataToServer(RequestCodes.LogoutRequestCode, {});
  };

  const joinRoom = (request: JoinRoomRequest) => {
    //console.log("Joining room with the id: " + request.roomId);
    setSelectedRoomId(request.roomId);
    joinedRoomId = request.roomId;
    sendDataToServer(RequestCodes.JoinRoomRequestCode, request);
  };

  const createRoom = (request: CreateRoomRequest) => {
    sendDataToServer(RequestCodes.CreateRoomRequestCode, request);
    newRoomData = {
      roomId: -1,
      roomName: request.roomName,
      maxUsers: request.maxUsers,
      questionCount: request.questionCount,
      answerTimeout: request.answerTimeout,
      isActive: 0,
      category: "General"
    };
  };

  const getPlayersInRoom = (request: GetPlayersInRoomRequest) => {
    sendDataToServer(RequestCodes.GetPlayersInRoomRequestCode, request);
  };

  const getRooms = () => {
    sendDataToServer(RequestCodes.GetRoomsRequestCode, {});
  };

  const getHighscores = () => {
    sendDataToServer(RequestCodes.GetHighScoreRequestCode, {});
  }

  const getPersonalStatistics = () => {
    sendDataToServer(RequestCodes.GetPersonalStatsRequestCode, {});
  }

  const closeRoom = () => {
    sendDataToServer(RequestCodes.CloseRoomRequestCode, {});
  }

  const startGame = () => {
    sendDataToServer(RequestCodes.StartGameRequestCode, {});
  }

  const getRoomState = () => {
    sendDataToServer(RequestCodes.GetRoomStateRequestCode, {});
  }

  const leaveRoom = () => {
    sendDataToServer(RequestCodes.LeaveRoomRequestCode, {});
  }

  const getQuestion = () => {
    sendDataToServer(RequestCodes.GetQuestionRequestCode, {});
  }

  const submitAnswer = (request: SubmitAnswerRequest) => {
    sendDataToServer(RequestCodes.SubmitAnswerRequestCode, request);
  }

  const getGameResults = () => {
    sendDataToServer(RequestCodes.GetGameResultsRequestCode, {});
  }

  const leaveGame = () => {
    sendDataToServer(RequestCodes.LeaveGameRequestCode, {});
  }

  return { login, signup, logout, joinRoom, createRoom, getHighscores, getPersonalStatistics, getPlayersInRoom, getRooms, closeRoom, startGame, getRoomState, leaveRoom, getGameResults, submitAnswer, leaveGame, getQuestion };
};

export default useClient;
