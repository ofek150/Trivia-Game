import React, { useState,  ReactNode } from 'react';
import { lightTheme, darkTheme } from "../theme";
import { ThemeProvider } from "@mui/material/styles";

export const ThemeModeContext = React.createContext<{
    themeMode: string;
    setThemeMode: React.Dispatch<React.SetStateAction<string>>;
    toggleThemeMode: () => void;
  }>({
    themeMode: "dark",
    setThemeMode: () => {},
    toggleThemeMode: () => {},
  });

interface ThemeModeProviderProps {
    children: ReactNode;
  }

  export const ThemeModeProvider: React.FC<ThemeModeProviderProps> = ({ children }) => {
    const [themeMode, setThemeMode] = useState("dark");
    
    const toggleThemeMode = () => {
      setThemeMode(prevMode => prevMode === "light" ? "dark" : "light");
    };

    const ThemeModeContextValue = {
      themeMode: themeMode,
      setThemeMode: setThemeMode,
      toggleThemeMode: toggleThemeMode,
    };

    const theme = themeMode === "light" ? lightTheme : darkTheme;

    return (
      <ThemeModeContext.Provider value={ThemeModeContextValue}>
        <ThemeProvider theme={theme}>
            {children}
        </ThemeProvider> 
      </ThemeModeContext.Provider>
    );
  };
