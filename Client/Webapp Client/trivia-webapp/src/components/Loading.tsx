import React from "react";
import { CircularProgress, Box, useTheme } from "@mui/material";

const Loading: React.FC = () => {
  const theme = useTheme();
  return (
    <Box
      sx={{
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        height: "100vh",
        background: theme.palette.background.default
      }}
    >
      <CircularProgress />
    </Box>
  );
};

export default Loading;
