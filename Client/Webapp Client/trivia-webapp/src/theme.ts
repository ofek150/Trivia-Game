import { createTheme } from "@mui/material/styles";

const darkThemePalette = {
  primary: "#FFA726",
  secondary: "#FFC107",
  textPrimary: "#FFFFFF",
  textSecondary: "#BDBDBD",
};

const lightThemePalette = {
  primary: "#FFC107",
  secondary: "#FFA726",
  textPrimary: "#212121",
  textSecondary: "#757575",
};

const commonTheme = {
  shape: {
    borderRadius: 6,
  },
  typography: {
    fontFamily: "Nunito, sans-serif", // Specify your desired font family here
  }
};

const darkTheme = createTheme({
  palette: {
    mode: "dark",
    primary: {
      main: darkThemePalette.primary,
    },
    secondary: {
      main: darkThemePalette.secondary,
    },
    text: {
      primary: darkThemePalette.textPrimary,
      secondary: darkThemePalette.textSecondary,
    },
    background: {
      default: "#121212",
      paper: "#1E1E1E",
    },
  },
  ...commonTheme,
});

const lightTheme = createTheme({
  palette: {
    mode: "light",
    primary: {
      main: lightThemePalette.primary,
    },
    secondary: {
      main: lightThemePalette.secondary,
    },
    text: {
      primary: lightThemePalette.textPrimary,
      secondary: lightThemePalette.textSecondary,
    },
    background: {
      default: "#F7F7F7",
      paper: "#FFFFFF",
    },
  },
  ...commonTheme,
});

export { darkTheme, lightTheme };
