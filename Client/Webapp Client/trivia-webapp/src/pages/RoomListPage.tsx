import React from "react";
import RoomList from "../components/RoomList";
import { Box, useTheme } from "@mui/material";

const RoomListPage: React.FC = () => {
  const theme = useTheme();

  return (
    <Box
      sx={{
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        height: "100vh",
        backgroundColor: theme.palette.background.default,
      }}
    >
      <RoomList />
    </Box>
  );
};

export default RoomListPage;
