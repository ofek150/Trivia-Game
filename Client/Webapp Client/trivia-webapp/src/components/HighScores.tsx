import React, { useEffect } from "react";
import { Typography, Box, useTheme, Container } from "@mui/material";
import { useHighscores } from "../contexts/CustomHooks";
import useClient from "../services/client";

const HighScores: React.FC = () => {
  const { Highscores } = useHighscores();
  const { getHighscores } = useClient();
  const theme = useTheme();

  useEffect(() => {
    getHighscores();
  }, []);

  const getMedalIcon = (index: number) => {
    if (index === 0) return "🏆";
    if (index === 1) return "🥇";
    if (index === 2) return "🥈";
    if (index === 3) return "🥉";
    return "⁉️";
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
          px: 4,
          py: 6,
          borderRadius: theme.shape.borderRadius,
          boxShadow: theme.shadows[3],
          background: theme.palette.background.paper,
        }}
      >
        <Typography variant="h3" component="h1" gutterBottom sx={{ color: theme.palette.text.primary }}>
          The Top 5 Players in the World:
        </Typography>

        <ol>
          {Object.entries(Highscores).map(([key, value], index) => {
            const [name, score] = String(value).split(": ");
            return (
              <li key={key}>
                <span>{getMedalIcon(index)}</span>
                {name}
              </li>
            );
          })}
        </ol>
      </Box>
    </Container>
  );
};

export default HighScores;
