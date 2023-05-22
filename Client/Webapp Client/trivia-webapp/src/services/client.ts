import { useEffect, useRef } from "react";

const SERVER_URL = "ws://127.0.0.1:9696";

export const useClient = () => {
  const socketRef = useRef<WebSocket | null>(null);

  // Establish the websocket connection
  useEffect(() => {
    socketRef.current = new WebSocket(SERVER_URL);
    socketRef.current.onmessage = (event) => {
      // Handle incoming data here
      console.log(event.data);
    };
    return () => {
      socketRef.current?.close();
    };
  }, []);
  

  const sendDataToServer = (requestCode: number, data: any) => {
    if (!socketRef.current) {
      console.error("Connection not established");
      return;
    }

    // Prepare the data to be sent
    const jsonData = JSON.stringify(data);
    const jsonDataLength = new TextEncoder().encode(jsonData).length.toString();
    const message = `${requestCode}${jsonDataLength}${jsonData}`;

    // Send the message as a binary string
    socketRef.current.send(new TextEncoder().encode(message));
    };


  const login = (username: string, password: string) => {
    sendDataToServer(1, { username, password });
  };

  const signup = (username: string, password: string) => {
    sendDataToServer(2, { username, password });
  };

  const logout = () => {
    sendDataToServer(3, {});
  };

  const joinRoom = (roomId: string) => {
    sendDataToServer(4, { roomId });
  };

  const createRoom = (roomName: string) => {
    sendDataToServer(5, { roomName });
  };

  // Implement other requests as needed...

  return { login, signup, logout, joinRoom, createRoom };
};
