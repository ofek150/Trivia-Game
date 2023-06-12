import React, { useContext, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { CurrentRoomDataContext } from "../contexts/CurrentRoomDataContext";

const RoomNavigator: React.FC = () => {
  const navigate = useNavigate();
  const { currentRoomData } = useContext(CurrentRoomDataContext);

  useEffect(() => {
    if (currentRoomData) {
      navigate(`/rooms/${currentRoomData.roomId}`);
    }
  }, [currentRoomData, navigate]);

  return null;
};

export default RoomNavigator;