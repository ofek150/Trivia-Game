import React from "react";
import { Box, useTheme } from "@mui/material";
import Login from "../components/Login";

const LoginPage: React.FC = () => {
  const theme = useTheme();

  return (
    <Box
      sx={{
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        height: "100vh",
        background: theme.palette.background.default,
      }}
    >
      <Login />
    </Box>
  );
};

export default LoginPage;
