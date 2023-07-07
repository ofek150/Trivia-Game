# Trivia Game (Magshimim Project)

This project is an interactive multiplayer trivia game developed as part of the Magshimim program. It was collaboratively created by a duo, leveraging React, TypeScript, and Material UI for the frontend, and C++ for the backend. The game establishes a connection between the frontend and backend using a proxy to communicate over websockets.
## Features

* Extensive trivia question database: The game includes a comprehensive collection of trivia questions from various categories, ensuring a diverse and engaging gameplay experience.
* Multiplayer mode: Challenge your friends in a trivia match and see who can answer the most questions correctly. Compete in real-time to test your knowledge against others.
* Interactive and intuitive user interface: The frontend provides a visually appealing and user-friendly interface, designed with Material UI components, making it easy and enjoyable to play the game.
* Real-time multiplayer functionality: Engage in thrilling trivia battles with your friends by connecting to the backend server via websockets. The backend handles the game logic and facilitates smooth communication between players.
* Score tracking and leaderboard: Keep track of your scores and compare them with other players on the leaderboard. Aim for the top spot and showcase your trivia expertise.
* Proxy connection to backend: Due to limitations with websockets connecting to normal sockets, the frontend utilizes a proxy to establish a connection with the backend server. This ensures seamless communication and a reliable gaming experience.

## Screenshots

## Getting Started

To get started with the trivia game project, follow these steps:

1. **Clone the repository:**
   
       git clone <repository-url>

3. **Build the backend server code**:
        Open the backend project in a C++ development environment (e.g., Visual Studio).
        Build the solution to compile the server code.

4. **Build the frontend client code**:
        Open the frontend project in a code editor (e.g., Visual Studio Code).
        Install the necessary dependencies by running the following command:
   
         npm install
   
   Build the project by running the following command:

        npm run build
        
5. **Start the backend server**:
        Run the compiled server application to start the backend.
        The backend server will listen for incoming connections from clients.

6. **Start the proxy server**:

       node proxy.js
   
7. **Start the frontend client**:
        Run the compiled frontend application to start the client.
        The client will establish a connection with the backend server through the proxy.

8. **Play the game**:
        Once the client is connected to the server, you can start playing the trivia game.

## Dependencies

The project has the following dependencies:

    React
    TypeScript
    Material UI
    C++ development environment (e.g., Visual Studio)
    Git (for cloning the repository)
    Node.js and npm (for frontend development)

Please ensure that you have the necessary development environments and tools installed before proceeding.
License

The project is licensed under the MIT License. Feel free to use, modify, and distribute the code as per the terms of the license.
Contact

We appreciate your interest in the trivia game project! If you have any questions or suggestions, please feel free to reach out to us:

## Contact Us
* Ofek Ifrah:
    * ofek080306@gmail.com
* Daniel Mordukhovich:
    * daniel.mordo06@gmail.com

We look forward to hearing from you and hope you enjoy playing the trivia game!
