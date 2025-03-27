const express = require('express');
const router = express.Router();
const minecraft = require('../services/minecraft');

// Get server status and player list
router.get('/status', async (req, res) => {
  try {
    const status = await minecraft.getServerStatus();
    res.json(status);
  } catch (err) {
    res.status(500).json({ error: 'Failed to get server status' });
  }
});

// Execute RCON command (admin only)
router.post('/command', async (req, res) => {
  const { command } = req.body;
  
  if (!command) {
    return res.status(400).json({ error: 'Command is required' });
  }
  
  try {
    const result = await minecraft.executeCommand(command);
    res.json(result);
  } catch (err) {
    res.status(500).json({ error: 'Failed to execute command' });
  }
});

module.exports = router;