import { useNavigate } from "react-router-dom";
import useClient from "../services/client";
import { Button, Typography, Box, useTheme, Container } from "@mui/material";
import { useRoomList, useUser, useResponse } from "../contexts/CustomHooks";

const MainMenu: React.FC = () => {
  const navigate = useNavigate();
  const { logout, leaveRoom } = useClient();
  const theme = useTheme();
  const { username, isInRoom } = useUser();
  const { setResponseMessage } = useResponse();
  const { setRoomList } = useRoomList();

  const handleLogout = async () => {
    try {
      await logout();
    } catch (error) {
      console.error(error);
    }
  };

  const handleStatisticsBtn = () => {
    navigate("/statistics");
  };

  if(isInRoom)
    {
      setResponseMessage("User is currently in a room.");
      setRoomList(null);
      leaveRoom();
    }

  return (
    <Container maxWidth="sm" sx={{ mt: 4, minHeight: "60%" }}>
      {/* <Typography variant="h3" component="h1" gutterBottom sx={{ color: theme.palette.text.primary, textAlign: "center", fontSize: "4em" }}>
        <span role="img" aria-label="Crown">👑</span> Trivia Game <span role="img" aria-label="Crown">👑</span>
      </Typography> */}
      <Typography variant="h5" component="h2" sx={{ color: theme.palette.text.primary, mb: 6, textAlign: "center", fontSize: "2em" }}>
        Welcome {username}, have fun!
      </Typography>
      <Box sx={{ display: "flex", flexDirection: "column", alignItems: "center", justifyContent: "center" }}>
        <Button
          fullWidth
          variant="contained"
          color="secondary"
          size="large"
          onClick={() => navigate("/rooms/list")}
          sx={{ mt: 3, fontSize: "1.8rem" }}
        >
          Rooms
        </Button>
        <Button
          fullWidth
          variant="contained"
          color="secondary"
          size="large"
          onClick={() => navigate("/create-room")}
          sx={{ mt: 2, fontSize: "1.8rem" }}
        >
          Create Room
        </Button>
        <Button
          fullWidth
          variant="contained"
          color="secondary"
          size="large"
          onClick={handleStatisticsBtn}
          sx={{ mt: 2, fontSize: "1.8rem" }}
        >
          Statistics
        </Button>
        <Button
          fullWidth
          variant="outlined"
          color="secondary"
          size="large"
          onClick={handleLogout}
          sx={{ mt: 3, fontSize: "1.8rem" }}
        >
          Logout
        </Button>
      </Box>
    </Container>
  );
};

export default MainMenu;
