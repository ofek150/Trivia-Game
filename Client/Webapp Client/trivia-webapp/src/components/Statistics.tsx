import React from "react";
import { useNavigate } from "react-router-dom";
import { Typography, Box, Button, useTheme, Container } from "@mui/material";
import GoBackBtn from "./GoBackBtn";

const Statistics: React.FC = () => {
  const navigate = useNavigate();
  const theme = useTheme();

  const handleHighScoreBtn = () => {
    navigate("/statistics/highscores");
  };

  const handlePersonalStatisticsBtn = () => {
    navigate("/statistics/personal");
  };

  return (
    <Container maxWidth="sm" sx={{ mt: 4 }}>
      <Typography variant="h3" component="h1" gutterBottom sx={{ color: theme.palette.text.primary, textAlign: "center", fontSize: "3rem", mt: 2 }}>
        Trivia Statistics
      </Typography>

      <Box sx={{ display: "flex", flexDirection: "column", alignItems: "center", justifyContent: "center", height: "60vh" }}>
        <Button
          variant="contained"
          color="secondary"
          size="large"
          onClick={handleHighScoreBtn}
          sx={{ mb: 2, fontSize: "1.8rem", width: "80%" }}
        >
          Highscores
        </Button>
        <Button
          variant="contained"
          color="secondary"
          size="large"
          onClick={handlePersonalStatisticsBtn}
          sx={{ fontSize: "1.8rem", width: "80%" }}
        >
          Personal Statistics
        </Button>
      </Box>

      <GoBackBtn />
    </Container>
  );
};

export default Statistics;
