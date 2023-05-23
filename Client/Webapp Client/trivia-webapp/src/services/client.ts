import { Console, error } from "console";
import { useEffect, useRef, useContext } from "react";
import { AuthContext } from "../App";
import { useNavigate } from "react-router-dom";
import { json } from "stream/consumers";
import { ResponseContext } from "../contexts/ResponseContext";
import WebSocketContext from "../contexts/WebSocketContext";
import {
  LoginRequest,
  SignupRequest,
  GetPlayersInRoomRequest,
  JoinRoomRequest,
  CreateRoomRequest,
  ParsedResponse
} from "../utils/types";
import { Socket } from "dgram";

const SERVER_URL = "ws://127.0.0.1:9696";
const RequestCodes = {
  LoginRequestCode: 1,
  SignupRequestCode: 2,
  LogoutRequestCode: 3,
  GetRoomsRequestCode: 4,
  JoinRoomRequestCode: 5,
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

  useEffect(() => {
    console.log(socket);
    console.log(socket?.readyState);
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
          console.log(data);
          break;
        case ResponseCodes.GetPlayersInRoomResponseCode:
          console.log(data);
          break;
        case ResponseCodes.CreateRoomResponseCode:
          console.log(data);
          break;
        case ResponseCodes.GetHighScoreResponseCode:
          console.log(data);
          break;
        case ResponseCodes.GetPersonalStatsResponseCode:
          console.log(data);
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
    sendDataToServer(RequestCodes.JoinRoomRequestCode, request);
  };

  const createRoom = (request: CreateRoomRequest) => {
    sendDataToServer(RequestCodes.CreateRoomRequestCode, request);
  };


  return { login, signup, logout, joinRoom, createRoom };
};

export default useClient;
