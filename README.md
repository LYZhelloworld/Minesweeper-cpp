# Minesweeper-cpp
CLI-style Minesweeper

## How to play
Starting the game, it will be initialised with a 10x10 map with 10 mines.

Hints (1~8) will be displayed in the map. An `X` means a flag. A `0` means a closed grid.

The X axis is the one on the left, and the Y axis is the one on the top. Please note that if the number of coordinate exceeds 10, only the last digit will be displayed.

The game is over when you click a mine, or you open all grids except mines. In either case, a "YOU WIN" or "YOU LOSE" message will be displayed, and you can either start a new game, or exit.

## Commands
- `new <width> <height>` or `n <width> <height>`: Starts new game.
- `click <x> <y>`, or `c <x> <y>`: Clicks a grid.
- `chord <x> <y>`, or `x <x> <y>`: Checks if adjacent square can be opened automatically.
- `flag <x> <y>`, or `f <x> <y>`: Marks a square as mine with flag `X`.
- `help`, `h`, or `?` :Shows help.
- `exit`, `quit`, or `q`: Exits.
