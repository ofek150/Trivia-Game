import React, { createContext, useState,  ReactNode } from 'react';

// REMOVE isUserAdmin

export const UserContext = createContext<{
  username: string;
  setUsername: React.Dispatch<React.SetStateAction<string>>;
  isRoomAdmin: boolean;
  setIsRoomAdmin: React.Dispatch<React.SetStateAction<boolean>>;
}>({
    username: '',
    setUsername: () => {},
    isRoomAdmin: false,
    setIsRoomAdmin: () => {}
});

interface ResponseProviderProps {
    children: ReactNode;
  }

  export const UserProvider: React.FC<ResponseProviderProps> = ({ children }) => {
    const [username, setUsername] = React.useState<string>('');
    const [isRoomAdmin, setIsRoomAdmin] = React.useState<boolean>(false);
    
    const UserContextValue = {
      username: username,
      setUsername: setUsername,
      isRoomAdmin: isRoomAdmin,
      setIsRoomAdmin: setIsRoomAdmin
    };

    return (
      <UserContext.Provider value={UserContextValue}>
        {children}
      </UserContext.Provider>
    );
  };
