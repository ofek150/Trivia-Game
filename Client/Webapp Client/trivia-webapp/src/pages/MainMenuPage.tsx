import React, {useEffect, useContext} from "react"
import MainMenu from "../components/MainMenu"
import { ResponseContext } from "../contexts/ResponseContext";

const MainMenuPage: React.FC = () => {

    const { setResponseMessage } = useContext(ResponseContext);
  
    useEffect(() => {
      setResponseMessage("");
    }, []);

    return (
        <div>
          <MainMenu/>
        </div>
    );
};

export default MainMenuPage;
