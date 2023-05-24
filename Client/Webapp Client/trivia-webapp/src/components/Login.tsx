import React, { useState, useContext} from "react";
import { useNavigate } from "react-router-dom";
import useClient from "../services/client";
import { ResponseContext } from "../contexts/ResponseContext";
import styles from "../styles/modules/Login.module.css"

const Login: React.FC = () => {
  const { login } = useClient();
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");

  const navigate = useNavigate();
  const { responseMessage, setResponseMessage } = useContext(ResponseContext);

  const handleLogin = async () => {
    try {
      await login({ username, password });
    } catch (error) {
      console.error(error);
    }
  };

  const handleSignup = () => {
    setResponseMessage("");
    navigate("/signup");
}

  return (
    <div className={styles.loginContainer}>
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
      <button onClick={handleLogin} className={styles.loginButton}>Login</button>
      <button onClick={ handleSignup } className={styles.signupButton}>Signup</button>
    </div>
  );
};

export default Login;
