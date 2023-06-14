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

  if (!currentRoomData || !currentRoomState) return null;

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
          <Typography variant="h3" sx={{ marginBottom: theme.spacing(2) }}>
            Room name: {currentRoomData.roomName}
          </Typography>
          <Typography variant="h4" sx={{ marginBottom: theme.spacing(1) }}>
            Connected users:
          </Typography>
          <List>
            {currentRoomState?.players.map((username) => (
              <ListItem key={String(username)} sx={{fontSize: "1.6em", textAlign: "center"}}>{username}</ListItem>
            ))}
          </List>
          <Typography variant="h5" sx={{ marginTop: theme.spacing(3), marginBottom: theme.spacing(3) }}>
            Admin: {currentRoomState?.players[0]}
          </Typography>
          {isRoomAdmin() && (
            <Button
              fullWidth
              variant="contained"
              onClick={startGame}
              sx={{ backgroundColor: theme.palette.secondary.main, marginTop: theme.spacing(2), height: "3em", fontSize: "1.4rem",
              "&:hover": {
                opacity: 0.8,
              }}}
            >
              Start game
            </Button>
          )}
          {isRoomAdmin() ? (
            <Button
              fullWidth
              variant="contained"
              onClick={closeRoom}
              sx={{ backgroundColor: theme.palette.secondary.main, marginTop: theme.spacing(2), height: "3em", fontSize: "1.4rem",
              "&:hover": {
                opacity: 0.8,
              }}}
            >
              Close room
            </Button>
          ) : (
            <Button
              fullWidth
              variant="contained"
              onClick={leaveRoom}
              sx={{ backgroundColor: theme.palette.secondary.main, marginTop: theme.spacing(2), height: "3em", fontSize: "1.4rem",
              "&:hover": {
                opacity: 0.8,
              }}}
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
