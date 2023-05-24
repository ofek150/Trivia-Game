import React, { useState, useContext } from "react"
import { useNavigate } from "react-router-dom";
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
    createRoom({roomName, maxUsers, questionCount, answerTimeout});
  }

  return (
      <div className={styles.createRoomContainer}>
        <GoBackBtn/>
        <input
          type="text"
          placeholder="Room name"
          value={roomName}
          onChange={(e) => setRoomName(e.target.value)}
        />
        <input
          type="number"
          placeholder="Max users"
          value={maxUsers}
          onChange={(e) => setMaxUsers(parseInt(e.target.value, 10))}
          min={2}
          max={5}
          // className={styles.passwordInput}
        />
        <input
          type="number"
          placeholder="Number of questions"
          value={questionCount}
          onChange={(e) => setQuestionCount(parseInt(e.target.value, 10))}
          min={5}
          max={10}
        />
        <input
          type="number"
          placeholder="Time for each question"
          value={answerTimeout}
          onChange={(e) => setAnswerTimeout(parseInt(e.target.value, 10))}
          min={1}
          max={60}
        />
        <div className={styles.responseMessage}>{responseMessage}</div>
        <button onClick={handleCreateRoom} className={styles.createRoomButton}>Create Room</button>
    </div>
    );
  };

export default CreateRoom;