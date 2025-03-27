# Minecraft Server Manager

## Project Goal

Create a web-based management interface for Minecraft servers that allows administrators to monitor player activity, execute commands, and manage server resources through an intuitive dashboard. This project aims to simplify Minecraft server administration for educational environments.

## Timeline

- **Phase 1 (Current)**: Core functionality - Server status, player listing, and basic RCON commands
- **Phase 2 (April 2025)**: Advanced features - Player management, world backups, and server performance monitoring
- **Phase 3 (June 2025)**: User management, permissions, and mobile-responsive design

## Quick Start

### Prerequisites

- [Docker](https://docs.docker.com/get-docker/) and [Docker Compose](https://docs.docker.com/compose/install/)
- Git

### Deployment

1. Clone the repository:
   ```bash
   git clone https://github.com/schto173/minecraft-manager.git
   cd minecraft-server-manager
   ```

2. Create an environment file:
   ```bash
   cp .env.example .env
   ```

3. Edit the `.env` file with your Minecraft server details:
   ```
   MC_HOST=minecraft
   MC_PORT=25565
   RCON_PORT=25575
   RCON_PASSWORD=your_secure_password
   ```

4. Start the application with Docker Compose:
   ```bash
   docker compose up -d
   ```

5. Access the web interface at `http://localhost:3000`

### Standalone Deployment (without Docker)

1. Install Node.js (v16 or later) and npm

2. Install dependencies:
   ```bash
   npm install
   ```

3. Create and configure the `.env` file as shown above

4. Start the application:
   ```bash
   npm start
   ```

## Docker Compose Configuration

The included `docker-compose.yml` sets up both the Minecraft server and web application:

```yaml
version: '3'
services:
  minecraft:
    image: itzg/minecraft-server
    ports:
      - "25565:25565"
    environment:
      EULA: "TRUE"
      RCON_PASSWORD: "${RCON_PASSWORD}"
      ENABLE_RCON: "true"
    volumes:
      - ./minecraft-data:/data
    restart: unless-stopped

  webapp:
    build: .
    ports:
      - "3000:3000"
    environment:
      - MC_HOST=minecraft
      - MC_PORT=25565
      - RCON_PORT=25575
      - RCON_PASSWORD=${RCON_PASSWORD}
    depends_on:
      - minecraft
    restart: unless-stopped
```

## Updating

To update the application:

1. Pull the latest changes:
   ```bash
   git pull
   ```

2. Rebuild and restart the containers:
   ```bash
   docker compose down
   docker compose up -d
   ```

## Troubleshooting

### Connection Issues

If the web app can't connect to the Minecraft server:

1. Verify the RCON password matches in both environments
2. Ensure the Minecraft server is fully started
3. Check logs: `docker compose logs minecraft`

### Port Conflicts

If you encounter port conflicts:

1. Edit the `docker-compose.yml` file to change the exposed ports
2. Update the `.env` file to match the new ports

## Project Structure

```
minecraft-server-manager/
├── server.js              # Main application entry point
├── routes/                # API endpoint definitions
├── services/              # Business logic modules
├── config.js              # Configuration settings
├── static/                # Frontend assets
├── Dockerfile             # Docker build instructions
├── docker-compose.yml     # Docker Compose configuration
├── .env.example           # Environment variables template
└── package.json           # Project dependencies
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for detailed information on how to contribute to this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [minecraft-server-util](https://github.com/PassTheMayo/minecraft-server-util) for server status queries
- [rcon-client](https://github.com/janispritzkau/rcon-client) for RCON communication
- [itzg/minecraft-server](https://github.com/itzg/docker-minecraft-server) for the Minecraft server Docker image