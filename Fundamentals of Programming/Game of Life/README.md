Game of Life
=============

Game of Life is a cellular automaton developed by John Conway in 1970. The "game" is a zero-player, meaning that it is a simulation that given an initial configuration, 
runs by itself and requires no user input. The application starts with a 8x8 grid of cells, which are either _alive_ or _dead_. At each generation, the following occurs:
  1. Any cell with fewer than 2 live neighbours dies
  2. Any cell with 2 or 3 live neighbours lives
  3. Any live cell with more than 3 live neighbours dies
  4. Any dead cell with **exactly** three live neighbours becomes a live cell

The application has the following functionalities:
  * display the initial 8x8 grid
  * add patterns to the board
  * create new generations
  * save/ load from a text file

Moreover, it has an object-oriented and layered architecture solution. 
