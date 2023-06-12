import React, { useContext } from "react";
import useClient from "../services/client";
import { CurrentRoomDataContext } from "../contexts/CurrentRoomDataContext";
import { CurrentRoomStateContext } from "../contexts/CurrentRoomStateContext";
import { UserContext } from "../contexts/UserContext";
import { Box, Typography, Button, List, ListItem, Container } from "@mui/material";
import { useTheme } from "@mui/material/styles";

const WaitingRoom: React.FC = () => {
  const theme = useTheme();
  const { currentRoomData, setCurrentRoomData } = useContext(CurrentRoomDataContext);
  const { currentRoomState } = useContext(CurrentRoomStateContext);
  const { leaveRoom, closeRoom, startGame } = useClient();
  const { username } = useContext(UserContext);

  const isRoomAdmin = () => {
    return currentRoomState?.players[0] === username;
  };

  if (!currentRoomData || !currentRoomState) return <div>Empty room data</div>;

  return (
    <Container
      maxWidth="sm"
      sx={{
        display: "flex",
        flexDirection: "column",
        alignItems: "center",
        color: theme.palette.text.primary,
        backgroundColor: theme.palette.background.default,
        padding: theme.spacing(2),
      }}
    >
      {currentRoomState?.hasGameBegan ? (
        <Typography variant="h3">Game</Typography>
      ) : (
        <Box sx={{ display: "flex", flexDirection: "column", alignItems: "center" }}>
          <Typography variant="h4" sx={{ marginBottom: theme.spacing(2) }}>
            Room name: {currentRoomData.roomName}
          </Typography>
          <Typography variant="h6" sx={{ marginBottom: theme.spacing(1) }}>
            Connected users:
          </Typography>
          <List>
            {currentRoomState?.players.map((username) => (
              <ListItem key={String(username)}>{username}</ListItem>
            ))}
          </List>
          <Typography variant="h6" sx={{ marginTop: theme.spacing(2) }}>
            Admin: {currentRoomState?.players[0]}
          </Typography>
          {isRoomAdmin() && (
            <Button
              variant="contained"
              onClick={startGame}
              sx={{ backgroundColor: theme.palette.secondary.main, marginTop: theme.spacing(2), height: "3em" }}
            >
              Start game
            </Button>
          )}
          {isRoomAdmin() ? (
            <Button
              variant="contained"
              onClick={closeRoom}
              sx={{ backgroundColor: theme.palette.secondary.main, marginTop: theme.spacing(1), height: "3em" }}
            >
              Close room
            </Button>
          ) : (
            <Button
              variant="contained"
              onClick={leaveRoom}
              sx={{ backgroundColor: theme.palette.secondary.main, marginTop: theme.spacing(2), height: "3em" }}
            >
              Leave room
            </Button>
          )}
        </Box>
      )}
    </Container>
  );
};

export default WaitingRoom;
