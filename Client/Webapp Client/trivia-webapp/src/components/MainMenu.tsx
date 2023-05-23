import React, { useContext, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { AuthContext } from "../App";
import useClient from "../services/client";

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

  return (
    <div className="main_menu-container">
      <button onClick={() => navigate("/room-list")}>rooms</button>
      <button onClick={handleLogout}>Logout</button>
    </div>
  );
};

export default MainMenu;
