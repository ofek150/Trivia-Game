import React, { useState } from "react"
import { useNavigate } from "react-router-dom";
import GoBackBtn from "./GoBackBtn";

const Signup: React.FC = () => {
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
  
    const handleSignup = () => {
      // SEND REQUEST
      console.log('Username:', username);
      console.log('Password:', password);
    };
  
    return (
      <div>
        <GoBackBtn/>
        Signup
      </div>
    );
  };

export default Signup;