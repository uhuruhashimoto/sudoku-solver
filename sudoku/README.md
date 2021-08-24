# Sudoku

### Overview
A directory that contains the main `create` and `solve` modules as well as a module for fuzz testing.

### Contents of Common Directory
* sudoku.c - the main Sudoku driver
* create.h & create.c - the Sudoku Creator's interface and implementation
* solve.h & solve.c - the Sudoku Solver's interface and implementation
* fuzztest.c - the generator for Sudoku tests
* Makefile - compilation procedure for Sudoku modules

### Usage
To build, run `make`.

To clean up, run `make clean`.

To call the Sudoku Creator, run `./sudoku create`

To call the Sudoku Solver, run `./sudoku solve`