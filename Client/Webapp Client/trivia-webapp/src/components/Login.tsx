import React, { useState, useContext } from "react";
import { useNavigate } from "react-router-dom";
import useClient from "../services/client";
import { ResponseContext } from "../contexts/ResponseContext";
import { TextField, Button, Typography, Container, Box, useTheme, Stack } from "@mui/material";

const Login: React.FC = () => {
  const { login } = useClient();
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const navigate = useNavigate();
  const { responseMessage, setResponseMessage } = useContext(ResponseContext);
  const theme = useTheme();

  const handleLogin = async () => {
    try {
      await login({ username, password });
    } catch (error) {
      console.error(error);
    }
  };

  const handleSignup = () => {
    setResponseMessage("");
    navigate("/signup");
  };

  return (
    <Container maxWidth="sm" >
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
        <Stack spacing={2} sx={{ width: "100%" }}>
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
            onClick={handleLogin}
            sx={{
              height: "3em",
              fontSize: "1.5rem",
              borderRadius: theme.shape.borderRadius,
              "&:hover": {
                opacity: 0.8,
              },
            }}
          >
            Login
          </Button>
          <Button
            fullWidth
            variant="outlined"
            color="secondary"
            onClick={handleSignup}
            sx={{
              height: "3em",
              fontSize: "1.5rem",
              borderRadius: theme.shape.borderRadius,
              color: theme.palette.text.primary,
              "&:hover": {
                color: theme.palette.secondary.main,
                bgcolor: "transparent",
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

export default Login;
