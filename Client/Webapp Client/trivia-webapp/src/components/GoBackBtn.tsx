import React, {useContext} from "react"
import { useNavigate} from "react-router-dom";
import { ResponseContext } from "../contexts/ResponseContext";

const GoBackBtn: React.FC = () => {
    const navigate = useNavigate();
    const { setResponseMessage } = useContext(ResponseContext);
    const handleGoBack = () => {
      navigate(-1); // Navigate back to the previous route
      setResponseMessage("");
    };

    return (
    <button className="back-arrow-button" onClick={handleGoBack}>
        <span className="back-arrow-icon">&#8592;</span>
      </button>
    );
  };

export default GoBackBtn;