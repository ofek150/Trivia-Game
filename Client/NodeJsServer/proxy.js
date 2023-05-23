const WebSocket = require("ws");
const net = require("net");

// Create a WebSocket server
const wss = new WebSocket.Server({ port: 9696 });

// Handle WebSocket connections
wss.on("connection", (ws) => {
  console.log("WebSocket connection established");

  // Create a regular socket client for each WebSocket connection and connect it to the server
  const socketClient = new net.Socket();
  socketClient.connect(6969, "127.0.0.1", () => {
    console.log("Connected to the socket server");
  });

  // Link the WebSocket and the socket client
  ws.socketClient = socketClient;

  // Handle WebSocket messages
  ws.on("message", (message) => {
    console.log("Received WebSocket message:", message);

    // Send the message to the socket server
    socketClient.write(message);
  });

  ws.on("error", (err) => {
    console.log("WebSocket connection error", err);

    // Close the corresponding socket connection to the server
    socketClient.end();
  });

  // Handle WebSocket close
  ws.on("close", () => {
    console.log("WebSocket connection closed");

    // Close the corresponding socket connection to the server
    socketClient.end();
  });

  // Handle socket data received from the server
  socketClient.on("data", (data) => {
    console.log("Received socket data:", data.toString());

    // Send the data to the corresponding WebSocket client
    if (ws.readyState === WebSocket.OPEN) {
      ws.send(data);
    }
  });

  // Handle socket close
  socketClient.on("close", () => {
    console.log("Socket connection closed");

    // Close the corresponding WebSocket connection
    ws.terminate();
  });
});
