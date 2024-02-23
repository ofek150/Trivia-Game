import React, { useEffect, useState } from "react";
import { Routes, Route, BrowserRouter as Router, Navigate, Outlet } from "react-router-dom";
import MainMenuPage from "../pages/MainMenuPage";
import LoginPage from "../pages/LoginPage";
import NotFoundPage from "../pages/NotFoundPage";
import SignupPage from "../pages/SignupPage";
import RoomListPage from "../pages/RoomListPage";
import CreateRoomPage from "../pages/CreateRoomPage";
import { ResponseProvider } from "../contexts/ResponseContext";
import { WebSocketProvider} from "../contexts/WebSocketContext";
import StatisticsPage from "../pages/StatisticsPage";
import HighScoresPage from "../pages/HighScoresPage";
import PersonalStatisticsPage from "../pages/PersonalStatisticsPage";
import RoomPage from "../pages/RoomPage";
import { RoomListProvider } from "../contexts/RoomListContext";
import { CurrentRoomDataProvider } from "../contexts/CurrentRoomDataContext";
import { SelectedRoomIdProvider } from "../contexts/SelectedRoomContext";
import { HighscoresProvider } from "../contexts/HighscoresContext";
import { PersonalStatisticsProvider } from "../contexts/PersonalStatisticsContext";
import { CurrentRoomStateProvider } from "../contexts/CurrentRoomStateContext";
import { UserProvider } from "../contexts/UserContext";
import { GameProvider } from "../contexts/GameContext";
import { AuthProvider } from "../contexts/AuthContext";
import RoomNavigator from "./RoomNavigator";
import ContextProvider from "../contexts/ContextProvider";
import { useAuth, useThemeMode } from "../contexts/CustomHooks";
import { ThemeModeProvider } from "../contexts/ThemeModeContext";

const ProtectedRoute: React.FC<{ element: React.ReactElement }> = ({ element }) => {
  const { isLoggedIn } = useAuth();

  return isLoggedIn ? element : <Navigate replace to="/login" />;
};

const NonProtectedRoute: React.FC<{ element: React.ReactElement }> = ({ element }) => {
  const { isLoggedIn } = useAuth();

  return isLoggedIn ? <Navigate replace to="/main-menu" /> : element;
};




const App: React.FC = () => {
  const { isLoggedIn } = useAuth();
  const { themeMode } = useThemeMode();

  useEffect(() => {
    console.log("Theme mode changed to ", themeMode);
  }, [themeMode])

  const providers = [
    WebSocketProvider,
    AuthProvider,
    ResponseProvider,
    UserProvider,
    HighscoresProvider,
    PersonalStatisticsProvider,
    RoomListProvider,
    SelectedRoomIdProvider,
    CurrentRoomDataProvider,
    CurrentRoomStateProvider,
    GameProvider
  ];

  return (
    <ThemeModeProvider>
      <ContextProvider providers={providers}>
        <Router>
          <RoomNavigator />
          <Routes>
            <Route path="/" element={<Navigate replace to="/login" />} />
            {/* Non protected routes */}
            <Route path="/login" element={<NonProtectedRoute element={<LoginPage />} />} />
            <Route path="/signup" element={<NonProtectedRoute element={<SignupPage />} />} />
            {/* Protected routes */}
            <Route path="/main-menu" element={<ProtectedRoute element={<MainMenuPage />} />} />
            <Route path="/rooms" element={<ProtectedRoute element={<Outlet />} />}>
              <Route path="list" element={<ProtectedRoute element={<RoomListPage />} />} />
              <Route path=":roomId" element={<ProtectedRoute element={<RoomPage />} />} />
            </Route>
            <Route path="/statistics" element={<ProtectedRoute element={<StatisticsPage />} />} />
            <Route path="/statistics/highscores" element={<ProtectedRoute element={<HighScoresPage />} />} />
            <Route path="/statistics/personal" element={<ProtectedRoute element={<PersonalStatisticsPage />} />} />
            <Route path="/create-room" element={<ProtectedRoute element={<CreateRoomPage />} />} />
            <Route path="*" element={<NotFoundPage />} />
          </Routes>
        </Router>
      </ContextProvider>
    </ThemeModeProvider>
  );
};

export default App;
