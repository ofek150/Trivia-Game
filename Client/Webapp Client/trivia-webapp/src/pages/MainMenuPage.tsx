import React, { useEffect, useContext } from "react";
import MainMenu from "../components/MainMenu";
import { ResponseContext } from "../contexts/ResponseContext";
import { Box, useTheme } from "@mui/material";

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
        justifyContent: "center",
        alignItems: "center",
        height: "100vh",
        background: theme.palette.background.default,
      }}
    >
      <MainMenu />
    </Box>
  );
};

export default MainMenuPage;
