import React, { useEffect } from "react";
import { useNavigate } from "react-router-dom";
import useClient from "../services/client";
import { useResponse, useRoomList, useUser } from "../contexts/CustomHooks";
import { Container, Box, Button, Typography, useTheme } from "@mui/material";
import GoBackBtn from "./GoBackBtn";

const RoomList: React.FC = () => {
  const { roomList, setRoomList } = useRoomList();
  const { responseMessage, setResponseMessage } = useResponse();
  const { joinRoom, getRooms, leaveRoom } = useClient();
  const { isInRoom } = useUser();
  const navigate = useNavigate();
  const theme = useTheme();

  useEffect(() => {
    if(isInRoom)
    {
      setResponseMessage("User is currently in a room.");
      setRoomList(null);
      leaveRoom();
    }
    else
    {
      setResponseMessage("");
      const intervalId = setInterval(getRooms, 2000);
      return () => clearInterval(intervalId);
    }
  }, [isInRoom])

  const handleJoinRoom = (roomId: number) => {
    joinRoom({ roomId });
  };

  return (
    <Container maxWidth="sm" sx={{height: "60%"}}>
      {isInRoom ? 
        <Typography variant="h3" component="h1" gutterBottom sx={{ color: theme.palette.text.primary, textAlign: "center" }}>
            {responseMessage}
        </Typography>
        :
        <Box sx={{ display: "flex", flexDirection: "column", alignItems: "center"}}>
          <GoBackBtn />
          <Typography variant="h3" component="h1" gutterBottom sx={{ color: theme.palette.text.primary,  textAlign: "center", mb: "1em" }}>
            Available Rooms
          </Typography>
          {roomList?.rooms.size ? (
            <Box sx={{ width: "100%", mt: theme.spacing(2) , display: "flex", flexDirection: "column", alignItems: "center" }}>
              {Array.from(roomList.rooms.values()).map((roomData) => (
                <Box key={roomData.roomId} sx={{ width: "60%", marginBottom: theme.spacing(3) }}>
                  <Button
                    onClick={() => handleJoinRoom(roomData.roomId)}
                    fullWidth
                    variant="contained"
                    color="secondary"
                    size="large"
                    sx={{ height: "3.5em", fontSize: "1.5rem" }}
                  >
                    {roomData.roomName}
                  </Button>
                </Box>
              ))}
            </Box>
          ) : (
            <Typography></Typography>
          )}
          <Typography variant="h5" component="h5" gutterBottom sx={{ color: theme.palette.text.primary, textAlign: "center" }}>
            {responseMessage}
          </Typography>
        </Box>
      }
    </Container>
  );
};

export default RoomList;
