module.exports = {
    MINECRAFT_SERVER: {
      host: process.env.MC_HOST || 'minecraft',
      port: parseInt(process.env.MC_PORT || '25565'),
      rconPort: parseInt(process.env.RCON_PORT || '25575'),
      rconPassword: process.env.RCON_PASSWORD
    }
  };