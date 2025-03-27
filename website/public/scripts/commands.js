class CommandManager {
    constructor() {
        this.commandInput = document.getElementById('commandInput');
        this.historyContainer = document.getElementById('commandHistory');
        this.setupEventListeners();
    }

    setupEventListeners() {
        // Enter key support
        this.commandInput.addEventListener('keypress', (e) => {
            if (e.key === 'Enter') {
                this.executeCommand();
            }
        });
    }

    async executeCommand() {
        const command = this.commandInput.value.trim();
        
        if (!command) return;

        try {
            const response = await fetch('/api/minecraft/command', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ command })
            });

            const result = await response.json();
            
            this.addToHistory(command, result);
            this.commandInput.value = '';
            
        } catch (error) {
            console.error('Error executing command:', error);
            this.addToHistory(command, { 
                success: false, 
                error: 'Failed to execute command' 
            });
        }
    }

    useTemplate(command) {
        this.commandInput.value = command;
        this.commandInput.focus();
    }

    addToHistory(command, result) {
        const historyItem = document.createElement('div');
        historyItem.className = `history-item ${result.success ? 'history-success' : 'history-error'}`;
        
        const timestamp = new Date().toLocaleString();
        
        historyItem.innerHTML = `
            <div class="history-content">
                <div class="history-command">${this.escapeHtml(command)}</div>
                ${result.response ? 
                    `<div class="history-response">${this.escapeHtml(result.response)}</div>` : 
                    result.error ? 
                    `<div class="history-response">${this.escapeHtml(result.error)}</div>` : 
                    ''}
            </div>
            <div class="history-time">${timestamp}</div>
        `;
        
        this.historyContainer.insertBefore(historyItem, this.historyContainer.firstChild);
    }

    escapeHtml(unsafe) {
        return unsafe
            .replace(/&/g, "&amp;")
            .replace(/</g, "&lt;")
            .replace(/>/g, "&gt;")
            .replace(/"/g, "&quot;")
            .replace(/'/g, "&#039;");
    }
}

// Initialize the command manager
const commandManager = new CommandManager();

// Global functions for HTML onclick handlers
window.executeCommand = () => commandManager.executeCommand();
window.useTemplate = (command) => commandManager.useTemplate(command);