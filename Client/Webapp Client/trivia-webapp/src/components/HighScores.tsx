import React, { useEffect, useContext } from "react";
import useClient from "../services/client";
import { HighscoresContext } from "../contexts/HighscoresContext";
import styles from "../styles/modules/HighScores.module.css";

const HighScores: React.FC = () => {
  const { Highscores } = useContext(HighscoresContext);
  const { getHighscores } = useClient();

  useEffect(() => {
    if(getHighscores)
    {
      getHighscores();
    }
  }, []);

  const getMedalIcon = (index: number) => {
    if (index === 0) return "🏆";
    if (index === 1) return "🥇";
    if (index === 2) return "🥈";
    if (index === 3) return "🥉";
    return "⁉️";
  };

  return (
    <div className={styles.HighScoresContainer}>
      <h1 className={styles.title}>The Top 5 Players in the World:</h1>
      <ol className={styles.highscoresList}>
        {Object.entries(Highscores).map(([key, value], index) => {
          const [name, score] = value.split(": ");
          return (
            <li key={key}>
              <span className={styles.medalIcon}>{getMedalIcon(index)}</span>
              {name}
            </li>
          );
        })}
      </ol>
    </div>
  );
};

export default HighScores;
