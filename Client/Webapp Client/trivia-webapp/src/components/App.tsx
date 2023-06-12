import React, { useState, useContext } from "react";
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
import { ThemeProvider } from "@mui/material/styles";
import { lightTheme, darkTheme } from "../theme";
import RoomNavigator from "./RoomNavigator";

export const AuthContext = React.createContext<{
  isLoggedIn: boolean;
  setIsLoggedIn: React.Dispatch<React.SetStateAction<boolean>>;
}>({ isLoggedIn: false, setIsLoggedIn: () => {} });

const ProtectedRoute: React.FC<{ element: React.ReactElement }> = ({ element }) => {
  const { isLoggedIn } = useContext(AuthContext);

  return isLoggedIn ? element : <Navigate to="/login" />;
};

const App: React.FC = () => {
  const [isLoggedIn, setIsLoggedIn] = useState(false);
  const [themeMode, setThemeMode] = useState("dark");

  const toggleThemeMode = () => {
    setThemeMode((prevMode) => (prevMode === "light" ? "dark" : "light"));
  };

  const theme = themeMode === "light" ? lightTheme : darkTheme;


  return (
    <ThemeProvider theme={theme}>
      <WebSocketProvider>
        <ResponseProvider>
          <AuthContext.Provider value={{ isLoggedIn, setIsLoggedIn }}>
            <UserProvider>
              <HighscoresProvider>
                <PersonalStatisticsProvider>
                  <RoomListProvider>
                    <SelectedRoomIdProvider>
                      <CurrentRoomDataProvider>
                        <CurrentRoomStateProvider>
                          <Router>
                            <RoomNavigator />
                            <Routes>
                              <Route path="/" element={<Navigate replace to="/login" />} />
                              <Route path="/login" element={isLoggedIn ? <Navigate replace to="/main-menu" /> : <LoginPage />} />
                              <Route path="/signup" element={isLoggedIn ? <Navigate replace to="/main-menu" /> : <SignupPage />} />
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
                        </CurrentRoomStateProvider>
                      </CurrentRoomDataProvider>
                    </SelectedRoomIdProvider>
                  </RoomListProvider>
                </PersonalStatisticsProvider>
              </HighscoresProvider>
            </UserProvider>
          </AuthContext.Provider>
        </ResponseProvider>
      </WebSocketProvider>
    </ThemeProvider>
  );
};

export default App;