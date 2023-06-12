import React, { useContext, useEffect } from "react";
import useClient from "../services/client";
import { CurrentRoomDataContext } from "../contexts/CurrentRoomDataContext";
import { CurrentRoomStateContext  } from "../contexts/CurrentRoomStateContext";
import { UserContext } from "../contexts/UserContext";

const Game: React.FC = () => {
  const { currentRoomData, setCurrentRoomData } = useContext(CurrentRoomDataContext);
  const { currentRoomState } = useContext(CurrentRoomStateContext);
  const { username } = useContext(UserContext);

  if(!currentRoomData || !currentRoomState) return <div>Empty room data</div>

  return (  
    <div>
        Game
    </div>
  );
};

export default Game;
