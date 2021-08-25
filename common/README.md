# Common

### Overview
The common directory (compiled to a library) holds modules and functionalities used for both create and solve modules.

### Contents of Common Directory
* board.h & board.c - the interface and implementation for Sudoku board and editable_spots struct
* file.h & file.c - the interface and implementation for file utilities
* ultilities.h & utilities.c - the interface and implementation for Sudoku utilities
* unittest.h - the interface for conducting unit tests
* Makefile - compilation procedure for unit tests

### Usage
To build, run `make unit`.

To clean up, run `make clean`.

To call the unit tests for board.c, run `./unit_board`

To call the unit tests for utilitiies.c, run `./unit_utilities`

### Credits
The following files were utilized from CS50 code:
* file.c / file.h
* unittest.h