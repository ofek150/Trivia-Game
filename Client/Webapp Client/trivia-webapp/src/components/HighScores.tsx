import React, { useState, useEffect, useContext } from "react";
import { useNavigate } from "react-router-dom";
import useClient from "../services/client";
import { HighscoresContext } from "../contexts/HighscoresContext";

const HighScores: React.FC = () => {
  const { Highscores } = useContext(HighscoresContext);
  const { getHighscores } = useClient();

  useEffect(() => {
    getHighscores();
  }, []);

  return (
    <div>
      <h2>Top users:</h2>
      <div>
        <ol>
          {Object.entries(Highscores).map(([key, value]) => {
            const [name, score] = value.split(" : ");
            return <li key={key}>{name}</li>;
          })}
        </ol>
      </div>
    </div>
  );
};

export default HighScores;
