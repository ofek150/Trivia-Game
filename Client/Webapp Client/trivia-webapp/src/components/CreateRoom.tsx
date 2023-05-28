import React, { useState, useContext } from "react"
import { ResponseContext } from "../contexts/ResponseContext";
import useClient from "../services/client";
import styles from "../styles/modules/CreateRoom.module.css"
import GoBackBtn from "./GoBackBtn";

const CreateRoom: React.FC = () => {
  const [roomName, setRoomName] = useState("");
  const [maxUsers, setMaxUsers] = useState(0);
  const [questionCount, setQuestionCount] = useState(0);
  const [answerTimeout, setAnswerTimeout] = useState(0);
  const { responseMessage, setResponseMessage } = useContext(ResponseContext);
  const { createRoom } = useClient();
  
  const handleCreateRoom = () => {
    if(roomName.length == 0 || maxUsers == 0 || questionCount == 0 || answerTimeout == 0)
    {
      setResponseMessage("Fields can't be empty!");
      return;
    }
    createRoom({ roomName, maxUsers, questionCount, answerTimeout });
  }

  const renderMaxUsersValue = maxUsers === 0 ? "" : maxUsers.toString();
  const renderQuestionCountValue = questionCount === 0 ? "" : questionCount.toString();
  const renderAnswerTimeoutValue = answerTimeout === 0 ? "" : answerTimeout.toString();

  return (
    <div className={styles.createRoomContainer}>
      <GoBackBtn />
      <input
        type="text"
        placeholder="Room name"
        value={roomName}
        onChange={(e) => setRoomName(e.target.value)}
      />
      <input
        type="number"
        placeholder="Max players"
        value={renderMaxUsersValue}
        onChange={(e) => setMaxUsers(parseInt(e.target.value, 10))}
        min={2}
        max={5}
      />
      <input
        type="number"
        placeholder="Number of questions"
        value={renderQuestionCountValue}
        onChange={(e) => setQuestionCount(parseInt(e.target.value, 10))}
        min={1}
        max={40}
      />
      <input
        type="number"
        placeholder="Time for each question"
        value={renderAnswerTimeoutValue}
        onChange={(e) => setAnswerTimeout(parseInt(e.target.value, 10))}
        min={1}
        max={120}
      />
      <div className={styles.responseMessage}>{responseMessage}</div>
      <button onClick={handleCreateRoom} className={styles.createRoomButton}>Create Room</button>
    </div>
  );
};

export default CreateRoom;