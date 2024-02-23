import { useContext } from "react";
import { ResponseContext } from "./ResponseContext";
import { CurrentRoomDataContext } from "./CurrentRoomDataContext";
import { SelectedRoomIdContext } from "./SelectedRoomContext";
import { CurrentRoomStateContext } from "./CurrentRoomStateContext";
import { RoomListContext } from "./RoomListContext";
import { PersonalStatisticsContext } from "./PersonalStatisticsContext";
import { HighscoresContext } from "./HighscoresContext";
import { UserContext } from "./UserContext";
import { GameContext } from "./GameContext";
import { WebSocketContext } from "./WebSocketContext";
import { AuthContext } from "./AuthContext";
import { ThemeModeContext } from "./ThemeModeContext";


export const useResponse = () => {
  const context = useContext(ResponseContext);
  if (!context) {
    console.log("useResponse must be used within a ResponseProvider");
  }
  return context;
};

export const useThemeMode = () => {
  const context = useContext(ThemeModeContext);
  if (!context) {
    console.log("useThemeMode must be used within a ThemeModeProvider");
  }
  return context;
};

export const useAuth = () => {
  const context = useContext(AuthContext);
  if (!context) {
    console.log("useAuth must be used within a AuthProvider");
  }
  return context;
};

export const useCurrentRoomData = () => {
  const context = useContext(CurrentRoomDataContext);
  if (!context) {
    console.log("useCurrentRoomData must be used within a CurrentRoomDataProvider");
  }
  return context;
};

export const useSelectedRoomId = () => {
    const context = useContext(SelectedRoomIdContext);
    if (!context) {
        console.log("useSelectedRoomId must be used within a SelectedRoomIdProvider");
    }
    return context;
  };

export const useCurrentRoomState = () => {
  const context = useContext(CurrentRoomStateContext);
  if (!context) {
    console.log("useCurrentRoomState must be used within a CurrentRoomStateProvider");
  }
  return context;
};

export const useRoomList = () => {
  const context = useContext(RoomListContext);
  if (!context) {
    console.log("useRoomList must be used within a RoomListProvider");
  }
  return context;
};

export const usePersonalStatistics = () => {
  const context = useContext(PersonalStatisticsContext);
  if (!context) {
    console.log("usePersonalStatistics must be used within a PersonalStatisticsProvider");
  }
  return context;
};

export const useHighscores = () => {
    const context = useContext(HighscoresContext);
    if (!context) {
        console.log("useHighscores must be used within a HighscoresProvider");
    }
    return context;
  };

export const useUser = () => {
  const context = useContext(UserContext);
  if (!context) {
    console.log("useUser must be used within a UserProvider");
  }
  return context;
};

export const useGame = () => {
    const context = useContext(GameContext);
    if (!context) {
      console.log("useGame must be used within a GameProvider");
    }
    return context;
  };
  

export const useWebSocket = () => {
  const context = useContext(WebSocketContext);
  if (!context) {
    console.log("useWebSocket must be used within a WebSocketProvider");
  }
  return context;
};
