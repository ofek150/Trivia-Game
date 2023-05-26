import React, { useState, useEffect, useContext } from "react";
import { useNavigate } from "react-router-dom";
import useClient from "../services/client";
import { PersonalStatisticsContext } from "../contexts/PersonalStatisticsContext";

const PersonalStatistics: React.FC = () => {
  const { personalStatistics } = useContext(PersonalStatisticsContext);
  const { getPersonalStatistics } = useClient();
  useEffect(() => {
    getPersonalStatistics();
  }, []);
  return (
      <div>
        <h1>Your statistics:</h1>
        <ul>
        {personalStatistics.map((stat: string) => (
          <li>{stat}</li>
          ))}
        </ul>
      </div>

    );
  };
export default PersonalStatistics;
