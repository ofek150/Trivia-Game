import React from "react"
import { useNavigate } from "react-router-dom";

const GoBackBtn: React.FC = () => {
    const navigate = useNavigate();
    const handleGoBack = () => {
      navigate(-1); // Navigate back to the previous route
    };

    return (
    <button className="back-arrow-button" onClick={handleGoBack}>
        <span className="back-arrow-icon">&#8592;</span>
      </button>
    );
  };

export default GoBackBtn;