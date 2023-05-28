import React, { createContext, useState,  ReactNode } from 'react';

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

    return (
      <HighscoresContext.Provider value={HighscoresContextValue}>
        {children}
      </HighscoresContext.Provider>
    );
  };
