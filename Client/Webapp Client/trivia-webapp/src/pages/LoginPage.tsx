import React from "react"
import Login from "../components/Login"
import { useNavigate } from "react-router-dom";

const LoginPage: React.FC = () => {
    const navigate = useNavigate();
    return (
        <div>
            <Login/>
            <button onClick={ () => {navigate("/signup")} }>Signup Page</button>
        </div>
    );
};

export default LoginPage;
