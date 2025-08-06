# Battleship Game 

## Overview

This project is a console-based implementation of the classic Battleship game, where players can compete against an computer or another player via standard input/output streams. The application supports two roles: `master` (sets up the game) and `slave` (joins the game). The game follows traditional Battleship rules but allows for customizable field sizes and ship counts.

## Features

- **Two Player Modes**: 
  - `master`: Sets up the game parameters (field size, ship counts).
  - `slave`: Joins the game with parameters provided by the `master`.
- **Customizable Game Settings**:
  - Adjustable field width and height.
  - Configurable number of ships (1x1 to 4x1 sizes).
- **Strategies**:
  - `ordered`: Shoots sequentially from (0,0).
  - `custom`: Random shooting (default).
- **File Operations**:
  - Save (`dump`) and load (`load`) game states to/from files.
- **Command-Based Interface**: All interactions are done via commands (e.g., `ping`, `shot`, `start`).

## How to Play

1. **Setup**:
   - Run the application in either `master` or `slave` mode using the `create` command.
   - For `master`, set the field dimensions and ship counts using `set` commands.
   - For `slave`, wait for the `master` to provide parameters or load a saved game.

2. **Start the Game**:
   - Use the `start` command to begin the game.
   - Players take turns shooting by entering coordinates (e.g., `shot X Y`).

3. **Gameplay**:
   - After each shot, the game responds with `miss`, `hit`, or `kill`.
   - The `finished`, `win`, and `lose` commands check the game status.

4. **Saving/Loading**:
   - Use `dump PATH` to save the current game state.
   - Use `load PATH` to load a saved game state.

## Commands

| Command                      | Description                                                                 |
|------------------------------|-----------------------------------------------------------------------------|
| `ping`                       | Test command; responds with `pong`.                                         |
| `exit`                       | Exits the application.                                                      |
| `create [master,slave]`      | Initializes the game in the specified role.                                 |
| `start`                      | Starts the game.                                                            |
| `stop`                       | Ends the current game.                                                      |
| `set width N`                | Sets the field width to `N`.                                                |
| `get width`                  | Returns the current field width.                                            |
| `set height N`               | Sets the field height to `N`.                                               |
| `get height`                 | Returns the current field height.                                           |
| `set count [1,2,3,4] N`      | Sets the number of ships of a specific size (1-4) to `N`.                   |
| `get count [1,2,3,4]`        | Returns the number of ships of a specific size.                             |
| `set strategy [ordered,custom]` | Sets the shooting strategy.                                              |
| `shot X Y`                   | Shoots at coordinates `(X,Y)`; responds with `miss`, `hit`, or `kill`.      |
| `shot`                       | Returns the AI's next shot coordinates.                                     |
| `set result [miss,hit,kill]` | Updates the result of the last shot (for AI tracking).                      |
| `finished`                   | Checks if the game is over; responds with `yes` or `no`.                    |
| `win`                        | Checks if the player won; responds with `yes` or `no`.                      |
| `lose`                       | Checks if the player lost; responds with `yes` or `no`.                     |
| `dump PATH`                  | Saves the current game state to a file at `PATH`.                           |
| `load PATH`                  | Loads a game state from a file at `PATH`.                                   |

## File Format for `dump`/`load`

The file is a plain text file with the following structure:
- First line: Field width and height (e.g., `10 10`).
- Subsequent lines: Ship descriptions (size, orientation, coordinates).  
  Example:
```
10 10
1 v 0 0
2 h 3 4
4 h 1 8
```

## Requirements

- C++ compiler (supporting C++11 or later).
- No external dependencies; uses standard libraries.

## Build and Run

1. Compile the source files:
 ```bash
 g++ -std=c++11 main.cpp field.cpp command.cpp -o battleship
./battleship
```
