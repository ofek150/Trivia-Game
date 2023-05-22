import React, { useContext } from "react";
import { useNavigate } from "react-router-dom";
import { AuthContext } from "../App";

const MainMenu: React.FC = () => {
  const navigate = useNavigate();
  const { isLoggedIn, setIsLoggedIn } = useContext(AuthContext);

  const handleLogout = () => {
    // Update the loggedIn state to false when logging out
    setIsLoggedIn(false);
    navigate("/login");
  };

  return (
    <div className="main_menu-container">
      <button onClick={() => navigate("/room-list")}>rooms</button>
      <button onClick={handleLogout}>Logout</button>
    </div>
  );
};

export default MainMenu;
