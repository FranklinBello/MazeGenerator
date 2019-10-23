# Maze Generator

## Description

This program generates an ortogonal rectangular maze in C using the depth first search recursive backtracking algorithm indicated in the Maze Generation [Wikipedia page](https://en.wikipedia.org/wiki/Maze_generation_algorithm).

## Usage

To execute the program, send as an inline parameter the number of rows and columns for the maze.

```cmd
\main.exe nrow ncol
```

Neither of these values can be greater than 127. Hence, the maximum dimension is 127x127 cells. By default, the program prints the result in a file called "Maze_{nrow}x{ncol}.txt" located in the same directory of the main.c file.

## Roadmap

Further development is aimed toward implementing more maze generation algorithms and creating a menu that allows the user to select the preferred method of maze generation. Some other tasks considered are:

- Changing the name of the output file so it inlcudes the date and time when it was created.
- Declaring the functions as prototypes and move their definitions to the end of the file.
- Or creating a header file with the functions and variables used to generate the maze.

## Acknowledgements

This project was inspired by Daniel Shiffman's [Coding Challenge #10: Maze Generator](https://www.youtube.com/watch?v=HyK_Q5rrcr4)

