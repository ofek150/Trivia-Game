import React, { useContext, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { CurrentRoomDataContext } from "../contexts/CurrentRoomDataContext";

const RoomNavigator: React.FC = () => {
  const navigate = useNavigate();
  const { currentRoomData } = useContext(CurrentRoomDataContext);

  useEffect(() => {
    if (currentRoomData) {
      console.log("Navigator: currentRoomData: ", currentRoomData);
      navigate(`/rooms/${currentRoomData.roomId}`);
    }
  }, [currentRoomData]);

  return null;
};

export default RoomNavigator;