const WebSocket = require('ws');
const net = require('net');

// Create a WebSocket server
const wss = new WebSocket.Server({ port: 9696 });

// Create a regular socket client and connect it to the server
const socketClient = new net.Socket();
socketClient.connect(6969, '127.0.0.1', () => {
    console.log('Connected to the socket server');
});

// Handle WebSocket connections
wss.on('connection', (ws) => {
    console.log('WebSocket connection established');

    // Handle WebSocket messages
    ws.on('message', (message) => {
        console.log('Received WebSocket message:', message);

        // Send the message to the socket server
        socketClient.write(message);
    });

    // Handle WebSocket close
    ws.on('close', () => {
        console.log('WebSocket connection closed');
    });
});

// Handle socket data received from the server
socketClient.on('data', (data) => {
    console.log('Received socket data:', data.toString());

    // Broadcast the data to all connected WebSocket clients
    wss.clients.forEach((client) => {
        if (client.readyState === WebSocket.OPEN) {
            client.send(data.toString());
        }
    });
});

// Handle socket close
socketClient.on('close', () => {
    console.log('Socket connection closed');
});
