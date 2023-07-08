import React, { useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { useCurrentRoomData } from "../contexts/CustomHooks";

const RoomNavigator: React.FC = () => {
  const navigate = useNavigate();
  const { currentRoomData } = useCurrentRoomData();

  useEffect(() => {
    if (currentRoomData) {
      navigate(`/rooms/${currentRoomData.roomId}`);
    }
  }, [currentRoomData]);

  return null;
};

export default RoomNavigator;