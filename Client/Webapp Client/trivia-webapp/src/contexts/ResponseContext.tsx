import React, { createContext, useState,  ReactNode } from 'react';

export const ResponseContext = createContext<{
  responseMessage: string;
  setResponseMessage: React.Dispatch<React.SetStateAction<string>>;
}>({
  responseMessage: '',
  setResponseMessage: () => {}
});

interface ResponseProviderProps {
    children: ReactNode;
  }

  export const ResponseProvider: React.FC<ResponseProviderProps> = ({ children }) => {
    const [responseMessage, setResponseMessage] = useState('');
    
    const responseContextValue = {
      responseMessage: responseMessage,
      setResponseMessage: setResponseMessage,
    };

    return (
      <ResponseContext.Provider value={responseContextValue}>
        {children}
      </ResponseContext.Provider>
    );
  };
