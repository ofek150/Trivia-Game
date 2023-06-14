import React, { useEffect, useContext } from "react";
import MainMenu from "../components/MainMenu";
import { ResponseContext } from "../contexts/ResponseContext";
import { Box, useTheme } from "@mui/material";
import Header from "../components/Header";

const MainMenuPage: React.FC = () => {
  const { setResponseMessage } = useContext(ResponseContext);
  const theme = useTheme();

  useEffect(() => {
    setResponseMessage("");
  }, []);

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
        <MainMenu />
      </Box>
    </Box>
  );
};

export default MainMenuPage;
