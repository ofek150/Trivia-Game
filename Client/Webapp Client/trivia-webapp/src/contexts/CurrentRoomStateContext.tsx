import React, { createContext, useState, ReactNode, useEffect } from "react";
import { RoomState } from "../utils/types";

interface CurrentRoomStateContextProps {
  currentRoomState: RoomState | null;
  setCurrentRoomState: (State: RoomState | null) => void;
}

const initialCurrentRoomState: RoomState | null = null;

export const CurrentRoomStateContext = createContext<CurrentRoomStateContextProps>({
  currentRoomState: initialCurrentRoomState,
  setCurrentRoomState: () => {}
});

interface RoomStateProviderProps {
  children: ReactNode;
}

export const CurrentRoomStateProvider: React.FC<RoomStateProviderProps> = ({ children }) => {
  const [currentRoomState, setCurrentRoomState] = useState<RoomState | null>(initialCurrentRoomState);

  useEffect(() => {
    console.log(currentRoomState);
  }, [currentRoomState])

  const currentRoomStateContextValue = {
    currentRoomState: currentRoomState,
    setCurrentRoomState: setCurrentRoomState,
  };

  return (
    <CurrentRoomStateContext.Provider value={currentRoomStateContextValue}>
      {children}
    </CurrentRoomStateContext.Provider>
  );
};