# Node.js Minecraft Server Manager - Developer Guide

## Project Overview

This application provides a web interface to monitor and manage a Minecraft server using Node.js and RCON. It's designed to be modular, allowing multiple developers to contribute features independently.

## Project Structure Explained

```
project-root/
├── server.js              # Main application entry point
├── routes/                # API endpoint definitions
│   └── minecraft.js       # Minecraft-related API routes
├── services/              # Business logic modules
│   └── minecraft.js       # Minecraft server interaction logic
├── config.js              # Configuration settings
├── static/                # Frontend assets (served directly)
│   ├── index.html         # Main landing page
│   ├── css/               # Stylesheets
│   ├── js/                # JavaScript files
│   │   ├── common.js      # Shared functionality
│   │   └── modules/       # Feature-specific JS
│   └── pages/             # Feature-specific HTML pages
├── .env.example           # Template for environment variables
└── package.json           # Project dependencies
```

### Key Components

1. **server.js**: The application entry point that:
   - Sets up the Express server
   - Configures middleware
   - Loads and registers route handlers
   - Starts the HTTP server

2. **routes/**: Contains API endpoint definitions
   - Each file groups related endpoints (e.g., `minecraft.js` for server status)
   - Handles HTTP requests and responses
   - Calls appropriate service functions

3. **services/**: Contains business logic
   - `minecraft.js` handles RCON communication with the Minecraft server
   - Separates logic from route handlers for better testing and reuse

4. **static/**: Frontend files served directly to the browser
   - `pages/`: Feature-specific HTML pages
   - `js/modules/`: JavaScript modules for each feature

## How to Add a New Feature

### 1. Backend (API) Development

Create a new route file if your feature needs new API endpoints:

```javascript
// routes/your-feature.js
const express = require('express');
const router = express.Router();
const minecraft = require('../services/minecraft');

// Example endpoint
router.get('/your-endpoint', async (req, res) => {
  try {
    // Your logic here
    res.json({ success: true, data: result });
  } catch (err) {
    res.status(500).json({ error: 'Error message' });
  }
});

module.exports = router;
```

Then register your routes in `server.js`:

```javascript
const yourFeatureRoutes = require('./routes/your-feature');
app.use('/api/your-feature', yourFeatureRoutes);
```

### 2. Frontend Development

Create a new HTML page for your feature:

```html
<!-- static/pages/your-feature.html -->
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Your Feature - Minecraft Server Manager</title>
  <link rel="stylesheet" href="../css/style.css">
</head>
<body>
  <header>
    <h1>Your Feature Name</h1>
    <nav>
      <a href="../index.html">Home</a>
    </nav>
  </header>

  <main>
    <!-- Your feature content here -->
  </main>

  <script src="../js/modules/your-feature.js"></script>
</body>
</html>
```

Create a JavaScript module for your feature:

```javascript
// static/js/modules/your-feature.js
document.addEventListener('DOMContentLoaded', () => {
  // Your feature's JavaScript code

  async function fetchData() {
    try {
      const response = await fetch('/api/your-feature/your-endpoint');
      const data = await response.json();
      // Update the UI with the data
    } catch (error) {
      console.error('Error:', error);
    }
  }

  // Initialize your feature
  fetchData();
});
```

### 3. Link Your Feature

Add a link to your feature on the main page:

```html
<!-- In static/index.html -->
<nav>
  <a href="pages/your-feature.html">Your Feature</a>
</nav>
```

## Working with RCON

The `services/minecraft.js` file provides functions to interact with the Minecraft server via RCON:

```javascript
// Example of using the executeCommand function
const result = await minecraft.executeCommand('give PlayerName diamond 1');
```

This executes Minecraft commands directly on the server. You can use this to build features like:
- Player teleportation
- Weather control
- Item distribution
- World management

## Testing Your Feature

1. Start the application: `npm run dev`
2. Access your feature page: `http://localhost:3000/pages/your-feature.html`
3. Test all functionality
4. Check browser console for errors

## Contribution Workflow

1. **Fork & Clone**: Fork the repository and clone it locally
2. **Branch**: Create a feature branch `git checkout -b feature/your-feature-name`
3. **Develop**: Add your feature following the structure above
4. **Test**: Ensure your feature works and doesn't break existing functionality
5. **Commit**: Make atomic commits with clear messages
6. **Push**: Push your branch to your fork
7. **Pull Request**: Create a PR with a description of your feature

## Best Practices

1. **Keep Features Modular**: Each feature should be self-contained
2. **Error Handling**: Always handle errors in both frontend and backend code
3. **Code Comments**: Document complex logic or Minecraft-specific functionality
4. **Responsive Design**: Ensure your UI works on different screen sizes
5. **API Documentation**: Document any new API endpoints you create

By following this structure, multiple developers can work on different features simultaneously with minimal conflicts.