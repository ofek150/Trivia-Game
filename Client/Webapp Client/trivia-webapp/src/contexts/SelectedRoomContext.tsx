import React, { createContext, useState,  ReactNode, useEffect } from 'react';

export const SelectedRoomIdContext = createContext<{
  selectedRoomId: number;
  setSelectedRoomId: React.Dispatch<React.SetStateAction<number>>;
}>({
  selectedRoomId: 0,
  setSelectedRoomId: () => {}
});

interface SelectedRoomIdProviderProps {
    children: ReactNode;
  }

  export const SelectedRoomIdProvider: React.FC<SelectedRoomIdProviderProps> = ({ children }) => {
    const [selectedRoomId, setSelectedRoomId] = useState(0);
    
    const selectedRoomIdContextValue = {
      selectedRoomId: selectedRoomId,
      setSelectedRoomId: setSelectedRoomId,
    };

    return (
      <SelectedRoomIdContext.Provider value={selectedRoomIdContextValue}>
        {children}
      </SelectedRoomIdContext.Provider>
    );
  };
