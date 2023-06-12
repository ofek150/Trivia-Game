import React, { useContext } from "react";
import { useNavigate } from "react-router-dom";
import { AuthContext } from "./App";
import useClient from "../services/client";
import { Button, Typography, Box, useTheme, Container } from "@mui/material";
import { UserContext } from "../contexts/UserContext";
import { ResponseContext } from "../contexts/ResponseContext";
import { RoomListContext } from "../contexts/RoomListContext";

const MainMenu: React.FC = () => {
  const navigate = useNavigate();
  const { logout, leaveRoom } = useClient();
  const theme = useTheme();
  const { username, isInRoom } = useContext(UserContext);
  const { setResponseMessage } = useContext(ResponseContext);
  const { setRoomList } = useContext(RoomListContext);

  const handleLogout = async () => {
    try {
      await logout();
    } catch (error) {
      console.error(error);
    }
  };

  const handleStatisticsBtn = () => {
    navigate("/statistics");
  };

  if(isInRoom)
    {
      setResponseMessage("User is currently in a room.");
      setRoomList(null);
      leaveRoom();
    }

  return (
    <Container maxWidth="sm" sx={{ mt: 4, minHeight: "60%" }}>
      <Typography variant="h3" component="h1" gutterBottom sx={{ color: theme.palette.text.primary, textAlign: "center", fontSize: "3rem" }}>
        <span role="img" aria-label="Crown">👑</span> Trivia Game <span role="img" aria-label="Crown">👑</span>
      </Typography>
      <Typography variant="h5" component="h2" sx={{ color: theme.palette.text.primary, mb: 6, textAlign: "center", fontSize: "2rem" }}>
        Welcome {username}, have fun!
      </Typography>
      <Box sx={{ display: "flex", flexDirection: "column", alignItems: "center" }}>
        <Button
          fullWidth
          variant="contained"
          color="secondary"
          size="large"
          onClick={() => navigate("/rooms/list")}
          sx={{ mt: 3, fontSize: "1.8rem" }}
        >
          Rooms
        </Button>
        <Button
          fullWidth
          variant="contained"
          color="secondary"
          size="large"
          onClick={() => navigate("/create-room")}
          sx={{ mt: 2, fontSize: "1.8rem" }}
        >
          Create Room
        </Button>
        <Button
          fullWidth
          variant="contained"
          color="secondary"
          size="large"
          onClick={handleStatisticsBtn}
          sx={{ mt: 2, fontSize: "1.8rem" }}
        >
          Statistics
        </Button>
        <Button
          fullWidth
          variant="outlined"
          color="secondary"
          size="large"
          onClick={handleLogout}
          sx={{ mt: 3, fontSize: "1.8rem" }}
        >
          Logout
        </Button>
      </Box>
    </Container>
  );
};

export default MainMenu;
