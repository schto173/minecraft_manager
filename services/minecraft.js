const util = require('minecraft-server-util');
const { Rcon } = require('rcon-client');
const config = require('../config');

const MC_SERVER = config.MINECRAFT_SERVER;

// Get server status and player list
async function getServerStatus() {
  try {
    const options = {
      timeout: 5000,
      enableSRV: true
    };

    const status = await util.status(MC_SERVER.host, MC_SERVER.port, options);
    
    return {
      online: status.players.online,
      max: status.players.max,
      version: status.version.name,
      players: status.players.sample || []
    };
  } catch (err) {
    console.error('Server Status Error:', err);
    return {
      online: 0,
      max: 0,
      version: 'Unknown',
      players: []
    };
  }
}

// Execute RCON command
async function executeCommand(command) {
  const rcon = new Rcon({
    host: MC_SERVER.host,
    port: MC_SERVER.rconPort,
    password: MC_SERVER.rconPassword
  });

  try {
    await rcon.connect();
    const response = await rcon.send(command);
    await rcon.end();
    return { success: true, response };
  } catch (err) {
    console.error('RCON Error:', err);
    return { success: false, error: err.message };
  }
}

module.exports = {
  getServerStatus,
  executeCommand
};