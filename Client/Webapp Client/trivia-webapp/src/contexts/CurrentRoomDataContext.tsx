import React, { createContext, useState, ReactNode, useEffect } from "react";
import { RoomData } from "../utils/types";

interface CurrentRoomDataContextProps {
  currentRoomData: RoomData | null;
  setCurrentRoomData: (data: RoomData | null) => void;
  connectedUsers: string[];
  setConnectedUsers: (users: string[]) => void;
}

const initialCurrentRoomData: RoomData | null = null;
const initialConnectedUsers: string[] = [];

export const CurrentRoomDataContext = createContext<CurrentRoomDataContextProps>({
  currentRoomData: initialCurrentRoomData,
  setCurrentRoomData: () => {},
  connectedUsers: initialConnectedUsers,
  setConnectedUsers: () => {},
});

interface RoomDataProviderProps {
  children: ReactNode;
}

export const CurrentRoomDataProvider: React.FC<RoomDataProviderProps> = ({ children }) => {
  const [currentRoomData, setCurrentRoomData] = useState<RoomData | null>(initialCurrentRoomData);
  const [connectedUsers, setConnectedUsers] = useState<string[]>(initialConnectedUsers);

  useEffect(() => {
    console.log(currentRoomData);
  }, [currentRoomData])

  const currentRoomDataContextValue = {
    currentRoomData: currentRoomData,
    setCurrentRoomData: setCurrentRoomData,
    connectedUsers: connectedUsers,
    setConnectedUsers: setConnectedUsers
  };

  return (
    <CurrentRoomDataContext.Provider value={currentRoomDataContextValue}>
      {children}
    </CurrentRoomDataContext.Provider>
  );
};