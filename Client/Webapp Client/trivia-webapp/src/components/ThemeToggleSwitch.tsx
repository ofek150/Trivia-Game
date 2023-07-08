import BrightnessHighIcon from '@mui/icons-material/BrightnessHigh';
import NightsStayIcon from '@mui/icons-material/NightsStay';
import { Switch, IconButton, Box } from "@mui/material";
import { useThemeMode } from "../contexts/CustomHooks";

const ThemeToggleSwitch: React.FC = () => {
    const { themeMode, toggleThemeMode } = useThemeMode();
    return (
      <Box>
          <IconButton edge="start" color="inherit" aria-label="mode">
            <BrightnessHighIcon />
          </IconButton>
          <Switch checked={themeMode === 'dark'} onChange={toggleThemeMode} />
          <IconButton edge="end" color="inherit" aria-label="mode">
            <NightsStayIcon />
          </IconButton>
      </Box>
      
  );
}

export default ThemeToggleSwitch;