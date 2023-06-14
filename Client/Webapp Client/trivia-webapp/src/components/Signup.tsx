import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import { TextField, Typography, Container, Box, useTheme, Button, Stack } from "@mui/material";
import { useResponse } from "../contexts/CustomHooks";
import useClient from "../services/client";
import GoBackBtn from "./GoBackBtn";

const Signup: React.FC = () => {
  const { signup } = useClient();
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [email, setEmail] = useState("");
  const { responseMessage } = useResponse();
  const theme = useTheme();
  const navigate = useNavigate();

  const handleSignup = async () => {
    try {
      await signup({ username, password, email });
    } catch (error) {
      console.error(error);
    }
  };

  const handleLogin = () => {
    navigate("/login");
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
          <Typography variant="subtitle1" color="error" sx={{ textAlign: "center", fontSize: "1.4em" }}>
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
          <Typography variant="subtitle1" color="text.primary" sx={{ textAlign: "center", fontSize: "1.2em" }}>
            Already have an account?{" "}
            <Button
              color="secondary"
              onClick={handleLogin}
              sx={{
                fontSize: "1.2em",
                textTransform: "none",
                borderRadius: theme.shape.borderRadius,
                "&:hover": {
                  color: theme.palette.secondary.main,
                  bgcolor: "transparent",
                },
              }}
            >
              Login
            </Button>
          </Typography>
        </Stack>
      </Box>
    </Container>
  );
};

export default Signup;
