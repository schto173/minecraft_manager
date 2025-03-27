document.addEventListener('DOMContentLoaded', () => {
    const statusContainer = document.getElementById('status-container');
    const playersContainer = document.getElementById('players-container');
    
    // Fetch server status
    async function fetchServerStatus() {
      try {
        const response = await fetch('/api/minecraft/status');
        const data = await response.json();
        
        // Update server stats
        statusContainer.innerHTML = `
          <p><strong>Status:</strong> Online</p>
          <p><strong>Players:</strong> ${data.online}/${data.max}</p>
          <p><strong>Version:</strong> ${data.version}</p>
        `;
        
        // Update player list
        if (data.players.length > 0) {
          playersContainer.innerHTML = data.players
            .map(player => `<li>${player.name}</li>`)
            .join('');
        } else {
          playersContainer.innerHTML = '<li>No players online</li>';
        }
      } catch (error) {
        statusContainer.innerHTML = '<p>Error connecting to server</p>';
        playersContainer.innerHTML = '<li>Could not fetch player list</li>';
        console.error('Error fetching server status:', error);
      }
    }
    
    // Initial fetch
    fetchServerStatus();
    
    // Refresh every 30 seconds
    setInterval(fetchServerStatus, 30000);
  });