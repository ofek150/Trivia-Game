import React, { createContext, useState,  ReactNode, useEffect } from 'react';

export const UserContext = createContext<{
  username: string;
  setUsername: React.Dispatch<React.SetStateAction<string>>;
  isInRoom: boolean;
  setIsInRoom: React.Dispatch<React.SetStateAction<boolean>>;
}>({
    username: '',
    setUsername: () => {},
    isInRoom: false,
    setIsInRoom: () => {}
});

interface ResponseProviderProps {
    children: ReactNode;
  }

  export const UserProvider: React.FC<ResponseProviderProps> = ({ children }) => {
    const [username, setUsername] = React.useState<string>('');
    const [isInRoom, setIsInRoom] = React.useState<boolean>(false);
    
    const UserContextValue = {
      username: username,
      setUsername: setUsername,
      isInRoom: isInRoom,
      setIsInRoom: setIsInRoom
    };

    return (
      <UserContext.Provider value={UserContextValue}>
        {children}
      </UserContext.Provider>
    );
  };
