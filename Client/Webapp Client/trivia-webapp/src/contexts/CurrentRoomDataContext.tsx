import React, { createContext, useState, ReactNode, useEffect } from "react";
import { RoomData } from "../utils/types";

interface CurrentRoomDataContextProps {
  currentRoomData: RoomData | null;
  setCurrentRoomData: (data: RoomData | null) => void;
}

const initialCurrentRoomData: RoomData | null = null;

export const CurrentRoomDataContext = createContext<CurrentRoomDataContextProps>({
  currentRoomData: initialCurrentRoomData,
  setCurrentRoomData: () => {}
});

interface RoomDataProviderProps {
  children: ReactNode;
}

export const CurrentRoomDataProvider: React.FC<RoomDataProviderProps> = ({ children }) => {
  const [currentRoomData, setCurrentRoomData] = useState<RoomData | null>(initialCurrentRoomData);

  useEffect(() => {
    console.log("currentRoomData(Context): ", currentRoomData);
  }, [currentRoomData])

  const currentRoomDataContextValue = {
    currentRoomData: currentRoomData,
    setCurrentRoomData: setCurrentRoomData
  };

  return (
    <CurrentRoomDataContext.Provider value={currentRoomDataContextValue}>
      {children}
    </CurrentRoomDataContext.Provider>
  );
};