import React, {useContext} from "react"
import { useNavigate} from "react-router-dom";
import { ResponseContext } from "../contexts/ResponseContext";
import styles from "../styles/modules/GoBackBtn.module.css"
const GoBackBtn: React.FC = () => {
    const navigate = useNavigate();
    const { setResponseMessage } = useContext(ResponseContext);
    const handleGoBack = () => {
      navigate(-1); // Navigate back to the previous route
      setResponseMessage("");
    };

    return (
    <button className={styles.btnGoBack} onClick={handleGoBack}>
        Go back
      </button>
    );
  };

export default GoBackBtn;