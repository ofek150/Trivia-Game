import React from "react";
import PersonalStatistics from "../components/PersonalStatistics";
import { Box, useTheme } from "@mui/material";

const PersonalStatisticsPage: React.FC = () => {
  const theme = useTheme();

  return (
    <Box sx={{ display: "flex", justifyContent: "center", alignItems: "center", height: "100vh", background: theme.palette.background.default }}>
      <PersonalStatistics />
    </Box>
  );
};

export default PersonalStatisticsPage;
