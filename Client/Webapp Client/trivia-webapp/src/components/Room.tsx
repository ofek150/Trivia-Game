import React, { useContext, useEffect, useState, useRef } from "react";
import useClient from "../services/client";
import { CurrentRoomDataContext } from "../contexts/CurrentRoomDataContext";
import { RoomListContext } from "../contexts/RoomListContext";
import { SelectedRoomIdContext } from "../contexts/SelectedRoomContext";
import { CurrentRoomStateContext } from "../contexts/CurrentRoomStateContext";
import { UserContext } from "../contexts/UserContext";
import WaitingRoom from "./WaitingRoom";
import Game from "./Game";
import { useNavigate } from "react-router-dom";
import Loading from "./Loading";
import { Container, useTheme } from "@mui/material";

const Room: React.FC = () => {
  const theme = useTheme();
  const { currentRoomData, setCurrentRoomData } = useContext(CurrentRoomDataContext);
  const { currentRoomState } = useContext(CurrentRoomStateContext);
  const { roomList } = useContext(RoomListContext);
  const { getRoomState  } = useClient();
  const { selectedRoomId } = useContext(SelectedRoomIdContext);
  const { username, isInRoom } = useContext(UserContext);
  const intervalId = useRef<number | undefined>(undefined);
  const navigate = useNavigate();


  // useEffect(() => {
  //   if (!currentRoomData) navigate("/main-menu");
  // }, [currentRoomData]);

  const isRoomAdmin = () => {
    return currentRoomState?.players[0] === username;
  };

  useEffect(() => {
    console.log("Current room data(room): ", currentRoomData);

    if (currentRoomData) {
      intervalId.current = window.setInterval(getRoomState, 2000);
    } else if (intervalId.current !== undefined) {
      window.clearInterval(intervalId.current);
      intervalId.current = undefined;
    }

    return () => {
      if (intervalId.current !== undefined) {
        window.clearInterval(intervalId.current);
      }
    };
  }, [currentRoomData]);

  // This useEffect hook clears the interval when the game has begun
  useEffect(() => {
    if (currentRoomState?.hasGameBegan && intervalId.current !== undefined) {
      window.clearInterval(intervalId.current);
      intervalId.current = undefined; // Reset the interval ID state
    }
  }, [currentRoomState?.hasGameBegan]);

  useEffect(() => {
    if (roomList) {
      const room = roomList.rooms.get(selectedRoomId);
      setCurrentRoomData(room !== undefined ? room : null);
    }
  }, [roomList]);

  //console.log("CurrentRoomData: ", currentRoomData, " CurrentRoomState: ", currentRoomState);
  if (!currentRoomData || !currentRoomState) return <div><Loading /></div>;

  return (
    <Container
      maxWidth="sm"
      sx={{
        backgroundColor: theme.palette.background.default,
        minHeight: "100vh",
        display: "flex",
        justifyContent: "center",
        alignItems: "center"
      }}
    >
      {currentRoomState?.hasGameBegan ? <Game /> : <WaitingRoom />}
    </Container>
  );
};

export default Room;
