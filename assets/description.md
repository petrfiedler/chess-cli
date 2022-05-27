# Chess Documentation

## Description

This is a program for playing classic chess game in the command line interface. It supports two-player mode and also artificial intelligence with 3 levels of difficulty.

## Controls

First, select the game settings by typing one of the options in square brackets.
In the game itself, you can move the chess pieces by typig coordinates of the move origin and destination (e.g. `e2 c4`).

You can also type commands:

- `help`: Show available commands.
- `info`: Show additional information about the game (castling, halfmove clock, number of moves).
- `quit`: Quit the game.
- `restart`: Go back to main menu.
- `save`: Save the game to file.

When the game is over, you will be prompted to play again.

## Saving and Loading Game

You can save the game state to a file or load it from a file.

To save the game, type: `save [file location]`. If the specified file location is valid, the game will be saved there.

You can load the game from main menu after selecting game type and difficulty.

## Testing

To run unit tests, go to `tests` directory and run: `make run`.

## Additional info

To run the game properly, your terminal should be able to print basic non-ASCII Unicode characters.

This program has been developed as a semestral work in BI-PA2 course on FIT CTU in 2022.
