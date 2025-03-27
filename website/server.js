const express = require('express');
const util = require('minecraft-server-util');
const { Rcon } = require('rcon-client');
const app = express();
const port = process.env.PORT || 3000;

// Middleware
app.use(express.static('public'));
app.use(express.json());

// Load routes
const serverRoutes = require('./routes/minecraft');

// Register routes
app.use('/api/minecraft', serverRoutes);

// Start server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});