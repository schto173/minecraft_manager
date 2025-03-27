
# Minecraft Server with Node.js RCON Integration

## Quick Start

1. Clone the repository:
   ```bash
   git clone https://github.com/schto173/minecraft_manager
   cd minecraft_manager
   ```

2. Edit the RCON password in the `.env` file:
   ```bash
   RCON_PASSWORD=your_secure_password_here
   ```

3. Start the services with debugging:
   ```bash
   docker compose up
   ```
   later you can use to detatch the running console.
      ```bash
   docker compose up -d
   ```

4. Access the web interface at `http://localhost:3000`.

## How It Works

The setup consists of two main services that communicate via RCON:

- **Minecraft Server (Port 25565)**:
  - Uses the `itzg/minecraft-server` Docker image.
  - RCON is enabled on port `25575`.
  - World data is stored in the `./minecraft-server/data` directory.

- **Node.js App (Port 3000)**:
  - Connects to the Minecraft server via RCON.
  - Provides a web interface and API endpoints.
  - Displays player positions and allows sending commands like giving items.

## API Endpoints

### GET `/api/players`
- Returns a list of online players and their positions.
- Also provides server version and player count.

### POST `/api/give-diamond`
- Gives a diamond to a specified player.
- Requires the player's name in the request body:
  ```json
  {
    "playerName": "Player1"
  }
  ```

## Updating

When new code is pushed to the repository, follow these steps to update:

1. Pull the latest changes:
   ```bash
   git pull
   ```

2. Rebuild and restart the services:
   ```bash
   docker compose down
   docker compose build
   docker compose up -d
   ```

## Stopping

To stop all services, run:
```bash
docker compose down
```

## Troubleshooting

### If the Node.js app can't connect:
- Verify that the RCON password in the `.env` file matches the one in the `docker-compose.yml` file.
- Ensure the Minecraft server is fully started.
- Check the logs for errors:
  ```bash
  docker compose logs -f
  ```

### If ports are already in use:
- Change the ports in the `docker-compose.yml` file.
- Default ports:
  - `25565` for the Minecraft server.
  - `3000` for the Node.js app.

## File Structure

```
minecraft-nodejs-project/
├── docker-compose.yml     # Service configuration
├── .env                   # RCON password
├── web/         
│   ├── Dockerfile         # Dockerfile for Node.js app
│   ├── src/            
│   │   └── app.js       # Main server code
│   └── public/            # Web interface
└── minecraft-server/   
    └── data/              # World data


## How to Contribute

This project allows you to add features to our Minecraft server management application. Follow these steps to contribute your code:

### Getting Started

1. Fork this repository
2. Clone your fork: `git clone https://github.com/YOUR-USERNAME/project-name.git`
3. Install dependencies: `npm install`
4. Create a feature branch: `git checkout -b feature/your-feature-name`

### Project Structure

- `server.js` - Main Express server
- `routes/` - API endpoints
- `services/` - Business logic
- `static/` - Frontend files
  - `pages/` - Feature pages (add yours here)
  - `js/modules/` - JavaScript modules

### Adding Your Feature

1. Create a new HTML page in `static/pages/your-feature.html`
2. Add JavaScript in `static/js/modules/your-feature.js`
3. If needed, create API endpoints in `routes/your-feature.js`

### Submitting Your Code

1. Test your changes locally
2. Commit with a descriptive message
3. Push to your fork: `git push origin feature/your-feature-name`
4. Create a pull request

```
```