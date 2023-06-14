import React, { useState, useContext } from "react";
import { useResponse } from "../contexts/CustomHooks";
import { TextField, Button, Typography, Container, Box, useTheme, Stack } from "@mui/material";
import useClient from "../services/client";
import GoBackBtn from "./GoBackBtn";

const CreateRoom: React.FC = () => {
  const { createRoom } = useClient();
  const [roomName, setRoomName] = useState("");
  const [maxUsers, setMaxUsers] = useState(0);
  const [questionCount, setQuestionCount] = useState(0);
  const [answerTimeout, setAnswerTimeout] = useState(0);
  const { responseMessage, setResponseMessage } = useResponse();
  const theme = useTheme();

  const handleCreateRoom = () => {
    if (roomName.length === 0 || maxUsers === 0 || questionCount === 0 || answerTimeout === 0) {
      setResponseMessage("Fields can't be empty!");
      return;
    }
    createRoom({ roomName, maxUsers, questionCount, answerTimeout });
  };

  return (
    <Container maxWidth="sm">
      <Box
        sx={{
          display: "flex",
          flexDirection: "column",
          justifyContent: "center",
          alignItems: "center",
          mt: 4,
          p: 4,
          borderRadius: theme.shape.borderRadius,
          boxShadow: theme.shadows[3],
          background: theme.palette.background.paper,
        }}
      >
        <GoBackBtn />

        <Stack spacing={2} sx={{ width: "100%" }}>
          <TextField
            fullWidth
            variant="outlined"
            placeholder="Room name"
            value={roomName}
            onChange={(e) => setRoomName(e.target.value)}
            inputProps={{ style: { fontSize: "1.6rem" } }}
          />
          <TextField
            fullWidth
            type="number"
            variant="outlined"
            placeholder="Max players"
            value={maxUsers === 0 ? "" : maxUsers.toString()}
            onChange={(e) => setMaxUsers(parseInt(e.target.value, 10))}
            inputProps={{ min: 2, max: 5, style: { fontSize: "1.6rem" } }}
          />
          <TextField
            fullWidth
            type="number"
            variant="outlined"
            placeholder="Number of questions"
            value={questionCount === 0 ? "" : questionCount.toString()}
            onChange={(e) => setQuestionCount(parseInt(e.target.value, 10))}
            inputProps={{ min: 1, max: 40, style: { fontSize: "1.6rem" } }}
          />
          <TextField
            fullWidth
            type="number"
            variant="outlined"
            placeholder="Time for each question"
            value={answerTimeout === 0 ? "" : answerTimeout.toString()}
            onChange={(e) => setAnswerTimeout(parseInt(e.target.value, 10))}
            inputProps={{ min: 1, max: 120, style: { fontSize: "1.6rem" } }}
          />
          <Typography variant="subtitle1" color="error" sx={{ textAlign: "center", fontSize: "1.4em" }}>
            {responseMessage}
          </Typography>
          <Button
            fullWidth
            variant="contained"
            color="primary"
            onClick={handleCreateRoom}
            sx={{
              height: "3em",
              fontSize: "1.6rem",
            }}
          >
            Create Room
          </Button>
        </Stack>
      </Box>
    </Container>
  );
};

export default CreateRoom;
