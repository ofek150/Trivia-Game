import React, { useContext, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { AuthContext } from "../App";
import useClient from "../services/client";
import styles from "../styles/modules/Login.module.css"

const MainMenu: React.FC = () => {
  const navigate = useNavigate();
  const { logout } = useClient();
  const { isLoggedIn, setIsLoggedIn } = useContext(AuthContext);
  
  const handleLogout = async () => {
    try {
      await logout();
    } catch (error) {
      console.error(error);
    }
  };

  const handleStatisticsBtn = () => {
    navigate("/statistics");
  }
  return (
    <div className={styles.loginContainer}>
      <div className={styles.title}>
        <h1>Trivia Game <span>Have fun!😊</span></h1>
      </div>
      <div className={styles.btnDiv}>
        <button className={styles.navigateBtn} onClick={() => navigate("/room-list")}>rooms</button> 
        <button className={styles.navigateBtn} onClick={() => navigate("/create-room")}>Create Room</button>
        <button className={styles.navigateBtn} onClick={() => navigate("/statistics")}>statistics</button>
      </div>
      <button className={styles.logOutBtn} onClick={handleLogout}>Logout</button>
    </div>
  );
};

export default MainMenu;
