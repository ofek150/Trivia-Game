import React, { createContext, useEffect, useState, FC, ReactNode, Dispatch, SetStateAction} from 'react';
import Loading from '../components/Loading';

type WebSocketContextType = {
  socket: WebSocket | null;
  setSocket: Dispatch<SetStateAction<WebSocket | null>>;      
  connectionEstablished: boolean;
};

const WebSocketContext = createContext<WebSocketContextType>({
  socket: null,
  setSocket: () => {},
  connectionEstablished: false,
});

const SERVER_URL = "ws://127.0.0.1:9696";

interface WebSocketProviderProps {
    children: ReactNode;
}

interface WebSocketProviderProps {
    children: ReactNode;
}

export const WebSocketProvider: FC<WebSocketProviderProps> = ({ children }) => {
  const [socket, setSocket] = useState<WebSocket | null>(null);
  const [connectionEstablished, setConnectionEstablished] = useState(false);

  useEffect(() => {
    const newSocket = new WebSocket(SERVER_URL);
    newSocket.binaryType = "arraybuffer";
    setSocket(newSocket);

    console.log("Establishing connection...");
  
    newSocket.onopen = () => {
        console.log("Connection established.");
      setConnectionEstablished(true);
    };

    newSocket.onclose = () => {
        console.log("Connection closed.");
      setConnectionEstablished(false);
    };

    return () => {
      newSocket.close();
    };
  }, []);

  if (!connectionEstablished) {
    return <Loading />
  }

  return (
    <WebSocketContext.Provider value={{ socket, setSocket, connectionEstablished }}>
      {children}
    </WebSocketContext.Provider>
  );
};


export default WebSocketContext;
