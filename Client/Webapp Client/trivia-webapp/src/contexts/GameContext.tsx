import React, { createContext, useState, useContext, ReactNode } from 'react';
import { GameData } from '../utils/types';

interface GameProviderProps {
  children: ReactNode;
}

export const GameContext = createContext<{
  gameData: GameData | null;
  setGameData: React.Dispatch<React.SetStateAction<GameData | null>>;
}>({
  gameData: null,
  setGameData: () => {},
});

export const GameProvider: React.FC<GameProviderProps> = ({ children }) => {
  const [gameData, setGameData] = useState<GameData | null>(null);

  const gameContextValue = {
    gameData: gameData,
    setGameData: setGameData
  };

  return (
    <GameContext.Provider value={gameContextValue}>
      {children}
    </GameContext.Provider>
  );
};
