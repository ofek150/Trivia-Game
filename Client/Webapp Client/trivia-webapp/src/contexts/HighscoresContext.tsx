import React, { createContext, useState,  ReactNode, useEffect } from 'react';

export const HighscoresContext = createContext<{
  Highscores: Object;
  setHighscores: React.Dispatch<React.SetStateAction<Object>>;
}>({
    Highscores: {},
  setHighscores: () => {}
});

interface HighscoresProviderProps {
    children: ReactNode;
  }

  export const HighscoresProvider: React.FC<HighscoresProviderProps> = ({ children }) => {
    const [Highscores, setHighscores] = useState(Object);
    
    const HighscoresContextValue = {
      Highscores: Highscores,
      setHighscores: setHighscores
    };

    useEffect(() => {
      console.log("Mounting HighscoresContext");
    } ,[]);

    return (
      <HighscoresContext.Provider value={HighscoresContextValue}>
        {children}
      </HighscoresContext.Provider>
    );
  };
