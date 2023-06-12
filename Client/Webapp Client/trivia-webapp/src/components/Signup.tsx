import React, { useContext, useState } from "react";
import { useNavigate } from "react-router-dom";
import { TextField, Typography, Container, Box, useTheme, Button, Stack } from "@mui/material";
import { ResponseContext } from "../contexts/ResponseContext";
import useClient from "../services/client";
import GoBackBtn from "./GoBackBtn";

const Signup: React.FC = () => {
  const { signup } = useClient();
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [email, setEmail] = useState("");
  const { responseMessage } = useContext(ResponseContext);
  const theme = useTheme();
  const navigate = useNavigate();

  const handleSignup = async () => {
    try {
      await signup({ username, password, email });
    } catch (error) {
      console.error(error);
    }
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
        <GoBackBtn />

        <Stack spacing={2} sx={{ width: "100%" }}>
          <TextField
            fullWidth
            variant="outlined"
            placeholder="Email"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            InputProps={{
              style: {
                fontSize: "1.5rem",
                borderRadius: theme.shape.borderRadius,
                background: theme.palette.background.paper,
              },
            }}
          />
          <TextField
            fullWidth
            variant="outlined"
            placeholder="Username"
            value={username}
            onChange={(e) => setUsername(e.target.value)}
            InputProps={{
              style: {
                fontSize: "1.5rem",
                borderRadius: theme.shape.borderRadius,
                background: theme.palette.background.paper,
              },
            }}
          />
          <TextField
            fullWidth
            type="password"
            variant="outlined"
            placeholder="Password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            InputProps={{
              autoComplete: "off",
              style: {
                fontSize: "1.5rem",
                borderRadius: theme.shape.borderRadius,
                background: theme.palette.background.paper,
              },
            }}
          />
          <Typography variant="subtitle1" color="textPrimary" sx={{ color: theme.palette.text.secondary }}>
            {responseMessage}
          </Typography>
          <Button
            fullWidth
            variant="contained"
            color="secondary"
            onClick={handleSignup}
            sx={{
              height: "3em",
              fontSize: "1.5rem",
              borderRadius: theme.shape.borderRadius,
              "&:hover": {
                opacity: 0.8,
              },
            }}
          >
            Signup
          </Button>
        </Stack>
      </Box>
    </Container>
  );
};

export default Signup;
