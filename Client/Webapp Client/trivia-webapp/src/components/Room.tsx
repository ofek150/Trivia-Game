import React, { useContext, useEffect } from "react";
import { RoomDataContext } from "../contexts/RoomDataContext";

const Room: React.FC = () => {
  const { roomData, setRoomData } = useContext(RoomDataContext);
  const { connectedUsers } = useContext(RoomDataContext);
  return (
    <div>
      <div>Room name: {roomData?.roomName}</div>
      <div>
        Connected users:
        <ul>
          {connectedUsers.map((user, index) => (
            <li key={index}>{user}</li>
          ))}
        </ul>
      </div>
    </div>
  );
};

export default Room;
