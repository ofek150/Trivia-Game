import React, { useState } from "react";
import { Routes, Route, BrowserRouter as Router, Navigate } from "react-router-dom";
import MainMenuPage from "./pages/MainMenuPage";
import LoginPage from "./pages/LoginPage";
import NotFoundPage from "./pages/NotFoundPage";
import SignupPage from "./pages/SignupPage";
import RoomListPage from "./pages/RoomListPage";
import CreateRoomPage from "./pages/CreateRoomPage";
import { ResponseProvider } from "./contexts/ResponseContext";
import { WebSocketProvider} from "./contexts/WebSocketContext";
import StatisticsPage from "./pages/StatisticsPage";
import HighScoresPage from "./pages/HighScoresPage";
import PersonalStatisticsPage from "./pages/PersonalStatisticsPage";
import RoomPage from "./pages/RoomPage";
import { RoomListProvider } from "./contexts/RoomListContext";
import { CurrentRoomDataProvider } from "./contexts/CurrentRoomDataContext";
import { SelectedRoomIdProvider } from "./contexts/SelectedRoomContext";

export const AuthContext = React.createContext<{
  isLoggedIn: boolean;
  setIsLoggedIn: React.Dispatch<React.SetStateAction<boolean>>;
}>({ isLoggedIn: false, setIsLoggedIn: () => {} });

const App: React.FC = () => {
  const [isLoggedIn, setIsLoggedIn] = useState(false);

  return (
    <WebSocketProvider>
      <ResponseProvider>
        <AuthContext.Provider value={{ isLoggedIn, setIsLoggedIn }}>
          <RoomListProvider>
            <SelectedRoomIdProvider>
              <CurrentRoomDataProvider>
                <Router>
                  <Routes>
                    <Route path="/" element={<Navigate to="/login" />} />
                    <Route path="/main-menu" element={isLoggedIn ? <MainMenuPage /> : <Navigate to="/login" />} />
                    <Route path="/login" element={isLoggedIn? <Navigate to = "/main-menu" /> : <LoginPage />} />
                    <Route path="/signup" element={isLoggedIn? <Navigate to = "/main-menu" /> : <SignupPage />} />
                    <Route path="/room-list" element={isLoggedIn? <RoomListPage /> : <Navigate to = "/login" />} />
                    <Route path="/room-list/room" element={isLoggedIn? <RoomPage /> : <Navigate to = "/login" />} />
                    <Route path="/statistics" element={isLoggedIn ? <StatisticsPage /> : <Navigate to="/login" />} />
                    <Route path="/statistics/highscores" element={isLoggedIn? <HighScoresPage /> : <Navigate to = "/login" />} />
                    <Route path="/statistics/personal" element={isLoggedIn ? <PersonalStatisticsPage /> : <Navigate to="/login" />} />
                    <Route path="/create-room" element={isLoggedIn? <CreateRoomPage /> : <Navigate to = "/login" />} />
                    <Route path="*" element={<NotFoundPage />} />
                  </Routes>
                </Router>
              </CurrentRoomDataProvider>
            </SelectedRoomIdProvider>  
          </RoomListProvider>
        </AuthContext.Provider>
      </ResponseProvider>
    </WebSocketProvider>
  );
};

export default App;
