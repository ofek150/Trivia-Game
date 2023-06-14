import React from 'react';
import { AppBar, Toolbar, Typography, Box } from '@mui/material';
import ThemeToggleSwitch from './ThemeToggleSwitch';

const Header: React.FC = () => {
  return (
    <AppBar position="static" sx={{ height: 'auto', py: 1 }}>
      <Box sx={{ 
        display: 'flex', 
        flexDirection: { xs: 'column', md: 'row' }, 
        alignItems: 'center', 
        justifyContent: 'center',
        textAlign: 'center'
      }}>
        <Box sx={{ order: { xs: 2, md: 1 }, display: { xs: 'none', md: 'flex' }}}>
          <Toolbar>
            <Box sx={{ width: 50 }} />  {/* Adjust the width to match the switch's width */}
          </Toolbar>
        </Box>
        <Box sx={{ flexGrow: 1, order: { xs: 1, md: 2 } }}>
          <Toolbar>
            <Typography variant="h2" sx={{ fontWeight: 700 }}>
              Trivia Game
            </Typography>
          </Toolbar>
        </Box>
        <Box sx={{ order: { xs: 2, md: 3 } }}>
          <Toolbar>
            <ThemeToggleSwitch />
          </Toolbar>
        </Box>
      </Box>
    </AppBar>
  );
};

export default Header;
