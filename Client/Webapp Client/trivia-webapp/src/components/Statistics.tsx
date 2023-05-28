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
      <div className={styles.title}>
        <h1>What would you like to know?<span>Trivia statistics</span></h1>
      </div>
      
      <div className={styles.btnDiv}>
        <button className={styles.navigateBtn} onClick={handleHighScoreBtn}>Highscores</button>
        <button className={styles.navigateBtn} onClick={handlePersonalStatisticsBtn}>Personal Statistics</button>
      </div>
      <GoBackBtn></GoBackBtn>
      
    </div>
  );
};

export default Statistics;