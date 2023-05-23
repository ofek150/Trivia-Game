import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import GoBackBtn from "./GoBackBtn";
import useClient from "../services/client";

const Signup: React.FC = () => {
  const { signup } = useClient();
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [email, setEmail] = useState("");

  const handleSignup = async () => {
    try {
      await signup({ username, password, email });
    } catch (error) {
      console.error(error);
    }
  };

  return (
    <div>
      <GoBackBtn/>
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
      <input
        type="email"
        placeholder="Email"
        value={email}
        onChange={(e) => setEmail(e.target.value)}
      />
      <button onClick={handleSignup}>Signup</button>
    </div>
  );
};

export default Signup;
