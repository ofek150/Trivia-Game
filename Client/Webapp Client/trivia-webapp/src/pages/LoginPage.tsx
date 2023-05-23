import React, {useContext} from "react"
import Login from "../components/Login"
import { useNavigate } from "react-router-dom";
import { ResponseContext } from "../contexts/ResponseContext";

const LoginPage: React.FC = () => {
    const navigate = useNavigate();
    const { setResponseMessage } = useContext(ResponseContext);
    

    const handleBtn = () => {
        setResponseMessage("");
        navigate("/signup");
    }

    return (
        <div>
            <Login/>
            <button onClick={ handleBtn }>Signup Page</button>
        </div>
    );
};

export default LoginPage;
