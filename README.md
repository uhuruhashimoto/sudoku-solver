# CS50 Final Project: Sudoku Creator & Solver

## Team: Uhuru Hashimoto, Megan Ren, Tyler Vergho, and Kelly Song


### Overview
The goal of this project was to build a program that would 1) create a unique Sudoku Puzzle and 2) solve a Sudoku Puzzle. For this project, we use a typical 9x9 structure of a Sudoku puzzle where a valid and completed Sudoku grid would include every number from 1 to 9 once in every row, once in every column, and once in every 3x3 squared region


### Organization
This project is organized into two main directories: a *Common* Directory and a *Sudoku* Directory. Here is what each directory contains:

#### Common
##### A directory (can be compiled to a library) of common functionalities needed for both create and solve modules.
* board.h & board.c - the interface and implementation for Sudoku board and editable_spots struct
* file.h & file.c - the interface and implementation for file utilities
* ultilities.h & utilities.c - the interface and implementation for Sudoku utilities
* unittest.h - the interface for unit tests
* Makefile - compilation procedure for unit tests

#### Sudoku
##### A directory that contains the main `create` and `solve` modules as well as a module for fuzz testing.
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


### Project Work Distribution
Here is how different tasks were *roughly* delegated throughout the project:

* Uhuru H. - mainly responsible for `solve` files, testing, and functionality
* Megan R. - mainly responsible for `board` files, testing, and functionality & writing backtrack algorithm
* Tyler V. - mainly responsible for `utilities` files, testing, and functionality & writing backtrack algorithm & `fuzztest` file
* Kelly S. - mainly responsible for `board` files, testing, and functionality & `markdown` files

* ALL TOGETHER - Brainstorming, `DESIGN.md`, testing, makefiles, & `create` files, implementation, and testing... etc.

NOTE: for enhanced collaboration, our team used peer/group programming for almost every part of the project. That being said, while each teammate was responsible for leading specific tasks, everyone contributed to each portion of the Sudoku project.