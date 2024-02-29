# Trivia Game (Magshimim Project)

This project is an interactive multiplayer trivia game developed as part of the Magshimim program. It was collaboratively created by a duo, leveraging React, TypeScript, and Material UI for the frontend, and C++ for the backend. The game establishes a connection between the frontend and backend using a proxy to communicate over websockets.

## Features

* Extensive trivia question database: The game includes a comprehensive collection of trivia questions from various categories, ensuring a diverse and engaging gameplay experience.
* Multiplayer mode: Challenge your friends in a trivia match and see who can answer the most questions correctly. Compete in real-time to test your knowledge against others.
* Interactive and intuitive user interface: The frontend provides a visually appealing and user-friendly interface, designed with Material UI components, making it easy and enjoyable to play the game.
* Real-time multiplayer functionality: Engage in thrilling trivia battles with your friends by connecting to the backend server via websockets. The backend handles the game logic and facilitates smooth communication between players.
* Score tracking and leaderboard: Keep track of your scores and compare them with other players on the leaderboard. Aim for the top spot and showcase your trivia expertise.
* Proxy connection to backend: Due to limitations with websockets connecting to normal sockets, the frontend utilizes a proxy to establish a connection with the backend server. This ensures seamless communication and a reliable gaming experience.


The project is licensed under the MIT License. Feel free to use, modify, and distribute the code as per the terms of the license.
