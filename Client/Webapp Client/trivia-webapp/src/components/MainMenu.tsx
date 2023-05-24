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
      <button onClick={() => navigate("/room-list")}>rooms</button>
      <button onClick={() => navigate("/create-room")}>Create Room</button>
      <button onClick={() => navigate("/statistics")}>statistics</button>
      <button onClick={handleLogout}>Logout</button>
    </div>
  );
};

export default MainMenu;
