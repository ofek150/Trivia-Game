import React, { useEffect, useContext } from "react";
import useClient from "../services/client";
import { PersonalStatisticsContext } from "../contexts/PersonalStatisticsContext";
import styles from "../styles/modules/PersonalStatistics.module.css";

const PersonalStatistics: React.FC = () => {
  const { personalStatistics } = useContext(PersonalStatisticsContext);
  const { getPersonalStatistics } = useClient();

  useEffect(() => {
    getPersonalStatistics();
  }, []);

  return (
    <div className={styles.PersonalStatsContainer}>
      <h1 className={styles.title}>Hi __ this is your personal statistics:</h1>
      <ul className={styles.statList}>
        {personalStatistics.map((stat: string, index: number) => (
          <li key={index} className={styles.statItem}>
            {stat}
          </li>
        ))}
      </ul>
    </div>
  );
};

export default PersonalStatistics;
