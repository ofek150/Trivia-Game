import React from "react";
import { Box, useTheme } from "@mui/material";
import Signup from "../components/Signup";

const SignupPage: React.FC = () => {
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
      <Signup />
    </Box>
  );
};

export default SignupPage;
