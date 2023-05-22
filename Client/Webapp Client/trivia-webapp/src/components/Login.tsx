import React, { useState, useContext } from "react"
import { useNavigate } from "react-router-dom";
import { AuthContext } from "../App";
import { useClient } from "../services/client";

const Login: React.FC = () => {

    const {login} = useClient();
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');

    const navigate = useNavigate();
    const { isLoggedIn, setIsLoggedIn } = useContext(AuthContext);
  
    const handleLogin = async () => {
      try {
        await login(username, password);
        // Handle the login success or failure accordingly
      } catch (error) {
        console.error('Login error:', error);
        // Handle the login error
      }
    };
  
    return (
      <div>
        <input
          type="text"
          placeholder="Username"
          value={username}
          onChange={(e) => setUsername(e.target.value)}
        />
        <input
          type="password"
          placeholder="Password"
          value={password}
          onChange={(e) => setPassword(e.target.value)}
        />
        <button onClick={handleLogin}>Login</button>
    </div>
    );
  };

export default Login;