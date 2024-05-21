### Mancala Board Game in C++

## Overview

This project is a C++ implementation of the traditional Mancala board game. The game features different types of players, including human, bad (random), and smart players. It includes comprehensive unit tests to verify the functionality of various components.

### Features
Players: Human, Bad, and Smart players with different move strategies.
Board: Configurable board size and initial bean count.
Game Mechanics: Standard Mancala rules including sowing, capturing, and endgame conditions.
Testing: Comprehensive tests to ensure the correctness of game logic and player interactions.

### Code Structure
main.cpp: Contains the main function, which includes test cases and a sample gameplay.
Game.h / Game.cpp: Defines the Game class, which manages the overall game flow.
Player.h / Player.cpp: Defines the Player class and its derived classes (HumanPlayer, BadPlayer, SmartPlayer).
Board.h / Board.cpp: Defines the Board class, which represents the Mancala board and its operations.
Side.h: Defines the Side enum used to specify North and South sides of the board.

### Example Tests
Player Tests: Verify that different types of players return valid moves.
Board Tests: Check board initialization, bean counts, and move operations.
Game Tests: Simulate a complete game and verify the correct endgame conditions and winner determination.
Sample Gameplay
The main.cpp file includes a sample gameplay scenario, where a HumanPlayer competes against a BadPlayer, followed by a BadPlayer competing against a SmartPlayer. You can observe the game flow and player interactions in the terminal output.

### Conclusion
This project demonstrates a complete implementation of the Mancala board game in C++, including different player strategies and comprehensive testing.
