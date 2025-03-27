# Contributing to Minecraft Server Manager

Thank you for your interest in contributing to the Minecraft Server Manager project! This document provides guidelines and instructions for contributing.

## Getting Started

### Prerequisites

- Node.js (v16 or later)
- npm or yarn
- Git
- Basic knowledge of JavaScript, HTML, and CSS
- Familiarity with Express.js is helpful

### Development Environment Setup

1. Fork the repository on GitHub
2. Clone your fork locally:
   ```bash
   git clone https://github.com/YOUR-USERNAME/minecraft-manager.git
   cd minecraft-manager
   ```

3. Install dependencies:
   ```bash
   npm install
   ```

4. Create a `.env` file from the template:
   ```bash
   cp .env.example .env
   ```

5. Start the development server:
   ```bash
   npm run dev
   ```

## Project Structure

```
project-root/
├── server.js              # Main application entry point
├── routes/                # API endpoint definitions
│   └── minecraft.js       # Minecraft-related API routes
├── services/              # Business logic modules
│   └── minecraft.js       # Minecraft server interaction logic
├── config.js              # Configuration settings
├── static/                # Frontend assets
│   ├── index.html         # Main landing page
│   ├── css/               # Stylesheets
│   ├── js/                # JavaScript files
│   │   ├── common.js      # Shared functionality
│   │   └── modules/       # Feature-specific JS
│   └── pages/             # Feature-specific HTML pages
```

## Adding a New Feature

### 1. Create a Feature Branch

```bash
git checkout -b feature/your-feature-name
```

### 2. Backend Development

If your feature requires new API endpoints:

1. Create a new route file in the `routes/` directory
2. Implement your API logic
3. Register your routes in `server.js`

Example route file:
```javascript
// routes/your-feature.js
const express = require('express');
const router = express.Router();
const minecraft = require('../services/minecraft');

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

### 3. Frontend Development

1. Create a new HTML page in `static/pages/`
2. Create a JavaScript module in `static/js/modules/`
3. Add a link to your feature on the main page

Example HTML page:
```html
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

## Coding Standards

### JavaScript

- Use ES6+ features
- Follow camelCase naming convention
- Add comments for complex logic
- Handle errors properly
- Use async/await for asynchronous operations

### HTML/CSS

- Use semantic HTML5 elements
- Follow the existing CSS structure
- Ensure responsive design
- Test on multiple browsers

## Testing

Before submitting your contribution:

1. Test your feature thoroughly
2. Ensure it works with the Minecraft server
3. Check for any console errors
4. Verify it doesn't break existing functionality

## Submitting Your Contribution

1. Commit your changes with clear, descriptive messages:
   ```bash
   git commit -m "Add feature: brief description"
   ```

2. Push to your fork:
   ```bash
   git push origin feature/your-feature-name
   ```

3. Create a Pull Request on GitHub:
   - Go to the original repository
   - Click "New Pull Request"
   - Select "compare across forks"
   - Select your fork and branch
   - Fill in the PR template with details about your changes

## Pull Request Process

1. Ensure your code follows the project's coding standards
2. Update documentation if necessary
3. Include screenshots if your changes include UI modifications
4. Link any related issues
5. Wait for code review and address any feedback

## Feature Ideas

If you're looking for ideas to contribute, consider:

- Player inventory viewer
- Server resource usage monitor
- World backup management
- Plugin/mod manager
- Server console viewer
- Player permission management
- Interactive world map

## Questions?

If you have questions or need help, please:
- Open an issue on GitHub
- Contact the project maintainer
- Ask in the project's discussion forum

Thank you for contributing to make Minecraft Server Manager better!