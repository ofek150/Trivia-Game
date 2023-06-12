import React from "react";
import { Box, useTheme } from "@mui/material";
import { CurrentRoomDataProvider } from "../contexts/CurrentRoomDataContext";
import Room from "../components/Room";

const RoomPage: React.FC = () => {
  const theme = useTheme();

  return (
    <Box
      sx={{
        backgroundColor: theme.palette.background.default,
        minHeight: "100vh",
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        padding: theme.spacing(2),
      }}
    >
        <Room />
    </Box>
  );
};

export default RoomPage;
