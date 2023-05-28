import React, { useContext, useState } from "react";
import { useNavigate } from "react-router-dom";
import GoBackBtn from "./GoBackBtn";
import useClient from "../services/client";
import { ResponseContext } from "../contexts/ResponseContext";
import styles from "../styles/modules/Signup.module.css"

const Signup: React.FC = () => {
  const { signup } = useClient();
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [email, setEmail] = useState("");
  const {responseMessage} = useContext(ResponseContext);

  const handleSignup = async () => {
    try {
      await signup({ username, password, email });
    } catch (error) {
      console.error(error);
    }
  };

  return (
    <div className={styles.signupContainer}>
      <GoBackBtn/>
      <input
        type="email"
        placeholder="Email"
        value={email}
        onChange={(e) => setEmail(e.target.value)}
        className={styles.emailInput}
      />
      <input
        type="text"
        placeholder="Username"
        value={username}
        onChange={(e) => setUsername(e.target.value)}
        className={styles.usernameInput}
      />
      <input
        type="password"
        placeholder="Password"
        value={password}
        onChange={(e) => setPassword(e.target.value)}
        className={styles.passwordInput}
      />
      <div className={styles.responseMessage}>{responseMessage}</div>
      <button onClick={handleSignup} className={styles.signupButton}>Signup</button>
    </div>
  );
};

export default Signup;
