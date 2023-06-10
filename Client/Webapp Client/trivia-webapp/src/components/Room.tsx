import React, { useContext, useEffect } from "react";
import useClient from "../services/client";
import { CurrentRoomDataContext } from "../contexts/CurrentRoomDataContext";
import { RoomListContext } from "../contexts/RoomListContext";
import { SelectedRoomIdContext } from "../contexts/SelectedRoomContext";
import { CurrentRoomStateContext  } from "../contexts/CurrentRoomStateContext";
import { UserContext } from "../contexts/UserContext";

const Room: React.FC = () => {
  const { currentRoomData, setCurrentRoomData } = useContext(CurrentRoomDataContext);
  const { currentRoomState } = useContext(CurrentRoomStateContext);
  const { roomList } = useContext(RoomListContext);
  const { getRoomState, leaveRoom, closeRoom, startGame } = useClient();
  const { selectedRoomId } = useContext(SelectedRoomIdContext);
  const { username } = useContext(UserContext);



  useEffect(() => {
    console.log("Room data: ", currentRoomData);
  }, [currentRoomData]);

  const isRoomAdmin = () => {
    return currentRoomState?.players[0] === username;
  }

  useEffect(() => {
    let intervalId: number | undefined;
    console.log("Current room data(room): ", currentRoomData);
    if (currentRoomData) {
      intervalId = window.setInterval(getRoomState, 2000);
    }
    return () => {
      if (intervalId !== undefined) {
        window.clearInterval(intervalId);
      }
    };
  }, [currentRoomData]);
  
  useEffect(() => {
    console.log("selectedRoomId: " + selectedRoomId + " Room list: " + roomList);
    if (roomList) {
      const room = roomList.rooms.get(selectedRoomId);
      setCurrentRoomData(room !== undefined ? room : null);
    }
  }, [roomList]);

  if(!currentRoomData || !currentRoomState) return <div>Empty room data</div>

  return (  
    <div>
      {currentRoomState?.hasGameBegan ? <div>Game</div> : 
      <div>
        <div>Room name: {currentRoomData.roomName}</div>
        <div>
          Connected users:
          <ol>
            {currentRoomState?.players.map((username) => (
              <li>{username}</li>
            ))}
          </ol>
          <h3>Admin: {currentRoomState?.players.length > 0 ? currentRoomState?.players[0] : "Error"}</h3>
          {isRoomAdmin() ? <button onClick={closeRoom}>Close room</button> : <button onClick={leaveRoom}>Leave room</button>}
          {isRoomAdmin() ? <button onClick={startGame}>Start game</button> : <></>}
        </div>
      </div>
      } 
    </div>
  );
};

export default Room;
