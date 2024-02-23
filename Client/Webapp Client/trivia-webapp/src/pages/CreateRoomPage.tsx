import React from "react";
import { Box, useTheme } from "@mui/material";
import CreateRoom from "../components/CreateRoom";

const CreateRoomPage: React.FC = () => {
  const theme = useTheme();

  return (
    <Box
      sx={{
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        height: "100vh",
        background: theme.palette.background.default,
      }}
    >
      <CreateRoom />
    </Box>
  );
};

export default CreateRoomPage;
