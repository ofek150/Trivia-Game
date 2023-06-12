import React, { useContext } from "react";
import { useNavigate, useLocation } from "react-router-dom";
import { ResponseContext } from "../contexts/ResponseContext";
import { IconButton, useTheme } from "@mui/material";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";

const GoBackBtn: React.FC = () => {
  const navigate = useNavigate();
  const location = useLocation();
  const { setResponseMessage } = useContext(ResponseContext);
  const theme = useTheme();

  const handleGoBack = () => {
    navigate(-1); // Navigate back to the previous route
    setResponseMessage("");
  };

  return (
    <IconButton
      onClick={handleGoBack}
      sx={{
        position: "absolute",
        top: theme.spacing(2),
        left: theme.spacing(2),
        backgroundColor: theme.palette.background.paper,
        "&:hover": {
          backgroundColor: theme.palette.background.paper,
        },
        width: "48px",
        height: "48px",
      }}
    >
      <ArrowBackIcon sx={{ fontSize: "28px" }} />
    </IconButton>
  );
};

export default GoBackBtn;
