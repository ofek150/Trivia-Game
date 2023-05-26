import React, { useState } from "react"
import { useNavigate } from "react-router-dom";
import styles from "../styles/modules/Statistics.module.css"
import GoBackBtn from "./GoBackBtn";
const Statistics: React.FC = () => {
  const navigate = useNavigate();
  const handleHighScoreBtn = () => {
    navigate("/statistics/highscores");
  } 
  const handlePersonalStatisticsBtn = () => {
    navigate("/statistics/personal");
  }
  return (
    <div className={styles.statisticsContainer}>
      <GoBackBtn />
      <button onClick={handleHighScoreBtn}>Highscores</button>
      <button onClick={handlePersonalStatisticsBtn}>Personal Statistics</button>
    </div>
  );
};

export default Statistics;