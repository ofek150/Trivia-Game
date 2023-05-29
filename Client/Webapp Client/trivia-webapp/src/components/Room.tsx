import React, { useContext, useEffect } from "react";
import useClient from "../services/client";
import { CurrentRoomDataContext } from "../contexts/CurrentRoomDataContext";
import { RoomListContext } from "../contexts/RoomListContext";
import { SelectedRoomIdContext } from "../contexts/SelectedRoomContext";

const Room: React.FC = () => {
  const { currentRoomData, setCurrentRoomData } = useContext(CurrentRoomDataContext);
  const { roomList } = useContext(RoomListContext);
  const { connectedUsers } = useContext(CurrentRoomDataContext);
  const { getPlayersInRoom, getRooms } = useClient();
  const { selectedRoomId } = useContext(SelectedRoomIdContext);

  useEffect(() => {
    getRooms();
  }, [selectedRoomId]);
  
  useEffect(() => {
    console.log("selectedRoomId: " + selectedRoomId + " Room list: " + roomList);
    if (roomList) {
      const room = roomList.rooms.get(selectedRoomId);
      setCurrentRoomData(room !== undefined ? room : null);
    }
  }, [roomList]);
  
  useEffect(() => {
    if(currentRoomData)
    {
      getPlayersInRoom({ roomId: currentRoomData.roomId });
    }
  }, [currentRoomData]);

  if(!currentRoomData) return <div>Empty room data</div>

  return (  
    <div>
      <div>Room name: {currentRoomData.roomName}</div>
      <div>
        Connected users:
        <ol>
          {connectedUsers.map((username) => (
            <li>{username}</li>
          ))}
        </ol>
        <h3>Admin: {connectedUsers.length > 0 ? connectedUsers[0] : "Error"}</h3>
      </div>
    </div>
  );
};

export default Room;
