import React from "react";
import Statistics from "../components/Statistics";
import { Box, useTheme } from "@mui/material";

const StatisticsPage: React.FC = () => {
  const theme = useTheme();

  return (
    <Box sx={{ display: "flex", justifyContent: "center", alignItems: "center", height: "100vh", background: theme.palette.background.default }}>
      <Statistics />
    </Box>
  );
};

export default StatisticsPage;
