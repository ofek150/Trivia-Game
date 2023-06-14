import { Box, Typography, List, ListItem, Container, ListItemButton } from "@mui/material";
import { useTheme } from "@mui/material/styles";
import { useGame } from "../contexts/CustomHooks";
import Loading from "./Loading";
import { GameData } from "../utils/types";

const Game: React.FC = () => {
  const theme = useTheme();
  const { gameData, setGameData } = useGame();

  const tempGameData: GameData = {
    question: "What year is it now?",
    answers: ["2021", "2023", "2022", "2020"]
  }
  setGameData(tempGameData);

  if (!gameData) return <Loading />;

  const handleAnswerClick = (answerId: number) => {
    console.log(answerId);
  };

  return (
    <Container
      maxWidth="sm"
      sx={{
        display: "flex",
        flexDirection: "column",
        alignItems: "center",
        color: theme.palette.text.primary,
        backgroundColor: theme.palette.background.default,
        padding: theme.spacing(2),
      }}
    >
      <Typography variant="h4" sx={{ marginBottom: theme.spacing(2), fontSize: "2em" }}>
        {gameData.question}
      </Typography>
      
      <List>
        {gameData.answers.map((answer: string, index: number) => (
          <ListItem key={index}>
            <ListItemButton onClick={() => handleAnswerClick(index)} sx={{ fontSize: "1.4em" }}>
              {answer}
            </ListItemButton>
          </ListItem>
        ))}
      </List>
    </Container>
  );
};

export default Game;
