import React, { createContext, useState,  ReactNode, useEffect } from 'react';

export const PersonalStatisticsContext = createContext<{
    personalStatistics: string[];
    setPersonalStatistics: React.Dispatch<React.SetStateAction<string[]>>;
}>({
    personalStatistics: [],
    setPersonalStatistics: () => {}
});

interface PersonalStatisticsProviderProps {
    children: ReactNode;
  }

  export const PersonalStatisticsProvider: React.FC<PersonalStatisticsProviderProps> = ({ children }) => {
    const [personalStatistics, setPersonalStatistics] = useState<string[]>([]);
    
    const PersonalStatisticsContextValue = {
        personalStatistics: personalStatistics,
        setPersonalStatistics: setPersonalStatistics
    };

    return (
      <PersonalStatisticsContext.Provider value={PersonalStatisticsContextValue}>
        {children}
      </PersonalStatisticsContext.Provider>
    );
  };
