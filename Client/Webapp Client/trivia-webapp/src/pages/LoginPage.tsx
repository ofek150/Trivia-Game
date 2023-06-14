import React from "react";
import { Box, useTheme } from "@mui/material";
import Login from "../components/Login";
import Header from "../components/Header";

const LoginPage: React.FC = () => {
  const theme = useTheme();

  return (
    <Box
      sx={{
        display: "flex",
        flexDirection: "column",
        justifyContent: "center",
        height: "100vh",
        background: theme.palette.background.default,
      }}
    >
      <Header />
      <Box
        sx={{
          marginBottom: theme.spacing(10),
          alignItems: "center",
          flexGrow: 1
        }}
      >
        <Login />
      </Box>
    </Box>
  );
};

export default LoginPage;
