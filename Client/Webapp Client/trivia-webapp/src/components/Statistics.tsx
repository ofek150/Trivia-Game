import React, { useState } from "react"
import { useNavigate } from "react-router-dom";
import styles from "../styles/modules/Statistics.module.css"
const Statistics: React.FC = () => {
  const navigate = useNavigate();
  const handleHighScoreBtn = () => {
    navigate("/statistics/highscores");
  } 
  const handlePersonalStatisticsBtn = () => {
    navigate("/statistics/personal");
  }
  return (
    <div>
      <h1 className={styles.title}>Statistics Page:</h1>
      <button onClick={handleHighScoreBtn}></button>
      <button onClick={handlePersonalStatisticsBtn}></button>
    </div>
  );
};

export default Statistics;