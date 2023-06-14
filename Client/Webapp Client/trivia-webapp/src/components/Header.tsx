import React from 'react';
import { AppBar, Toolbar, Typography, Switch, IconButton, useTheme } from '@mui/material';
import { useThemeMode } from '../contexts/CustomHooks';
import BrightnessHighIcon from '@mui/icons-material/BrightnessHigh';
import NightsStayIcon from '@mui/icons-material/NightsStay';
import { Box } from '@mui/system';

const Header = () => {
  const { themeMode, toggleThemeMode } = useThemeMode();
  const theme = useTheme();

  return (
    <AppBar position="static" sx={{ height: "10vh", display: "flex", alignItems: "center", justifyContent: "center"}}>
      <Toolbar sx={{ width: "100%"}}>
        <Box sx={{ margin: "0 auto" }}>
          <Typography variant="h2" component="div" sx={{ fontWeight: "700" }}>
            <span role="img" aria-label="Crown">👑</span> Trivia Game <span role="img" aria-label="Crown">👑</span>
          </Typography>
        </Box>
      </Toolbar>
      
      <Toolbar sx={{position: "absolute", top: theme.spacing(2), right: theme.spacing(2),}}>
        <IconButton edge="start" color="inherit" aria-label="mode">
          <BrightnessHighIcon />
        </IconButton>
        <Switch checked={themeMode === 'dark'} onChange={toggleThemeMode} />
        <IconButton edge="end" color="inherit" aria-label="mode">
          <NightsStayIcon />
        </IconButton>
      </Toolbar>
    </AppBar>
  );
};

export default Header;
