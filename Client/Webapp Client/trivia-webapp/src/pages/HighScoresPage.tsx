import React from "react";
import HighScores from "../components/HighScores";
import { Box, useTheme } from "@mui/material";

const HighScoresPage: React.FC = () => {
  const theme = useTheme();

  return (
    <Box sx={{ display: "flex", justifyContent: "center", alignItems: "center", height: "100vh", background: theme.palette.background.default }}>
      <HighScores />
    </Box>
  );
};

export default HighScoresPage;
