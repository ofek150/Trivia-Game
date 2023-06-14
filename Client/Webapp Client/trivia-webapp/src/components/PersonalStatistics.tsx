import React, { useEffect } from "react";
import useClient from "../services/client";
import { useUser, usePersonalStatistics } from "../contexts/CustomHooks";
import { Typography, Box, useTheme, Container } from "@mui/material";

const PersonalStatistics: React.FC = () => {
  const { personalStatistics } = usePersonalStatistics();
  const { getPersonalStatistics } = useClient();
  const { username } = useUser();
  const theme = useTheme();

  useEffect(() => {
    getPersonalStatistics();
  }, []);

  return (
    <Container maxWidth="sm" sx={{ mt: 4 }}>
      <Typography variant="h3" component="h1" gutterBottom sx={{ color: theme.palette.text.primary, textAlign: "center", fontSize: "2.5rem" }}>
        Hi {username}, this is your personal statistics:
      </Typography>
      <Box sx={{ background: theme.palette.background.paper, borderRadius: theme.shape.borderRadius, boxShadow: theme.shadows[3], p: 4 }}>
        <ul>
          {personalStatistics.map((stat: string, index: number) => (
            <li key={index}>
              <Typography variant="subtitle1" color="textPrimary" sx={{ mt: 2 }}>
                {stat}
              </Typography>
            </li>
          ))}
        </ul>
      </Box>
    </Container>
  );
};

export default PersonalStatistics;
