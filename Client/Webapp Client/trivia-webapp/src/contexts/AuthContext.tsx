import React, { createContext, useState, ReactNode, useEffect} from "react";
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

interface AuthDataProviderProps {
    children: ReactNode;
}

export const AuthContext = React.createContext<{
    isLoggedIn: boolean;
    setIsLoggedIn: React.Dispatch<React.SetStateAction<boolean>>;
  }>({ isLoggedIn: false, setIsLoggedIn: () => {} });

export const AuthProvider: React.FC<AuthDataProviderProps > = ({ children }) => {
    const [isLoggedIn, setIsLoggedIn] = useState(false);

    // useEffect(() => {
    //     console.log("isLoggedIn: ", isLoggedIn);
    // }, [isLoggedIn]);
  
    return (
      <AuthContext.Provider value={{ isLoggedIn, setIsLoggedIn }}>
        {children}
      </AuthContext.Provider>
    );
  };