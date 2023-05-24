import React, { createContext, useState, ReactNode, useEffect } from "react";
import { RoomData } from "../utils/types";

interface RoomDataContextProps {
  roomData: RoomData | null;
  setRoomData: (data: RoomData | null) => void;
  connectedUsers: string[];
  setConnectedUsers: (users: string[]) => void;
}

const initialRoomData: RoomData | null = null;
const initialConnectedUsers: string[] = [];

const RoomDataContext = createContext<RoomDataContextProps>({
  roomData: initialRoomData,
  setRoomData: () => {},
  connectedUsers: initialConnectedUsers,
  setConnectedUsers: () => {},
});

interface RoomDataProviderProps {
  children: ReactNode;
}

const RoomDataProvider: React.FC<RoomDataProviderProps> = ({ children }) => {
  const [roomData, setRoomData] = useState<RoomData | null>(initialRoomData);
  const [connectedUsers, setConnectedUsers] = useState<string[]>(initialConnectedUsers);

  console.log(roomData);

  useEffect(() => {
    console.log(roomData);
  }, [roomData])

  return (
    <RoomDataContext.Provider value={{ roomData, setRoomData, connectedUsers, setConnectedUsers }}>
      {children}
    </RoomDataContext.Provider>
  );
};

export { RoomDataContext, RoomDataProvider };
