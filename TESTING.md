# Sudoku Testing Documentation
## CS50 Summer 2021

### Usage

Make the fuzztest executable with `make fuzztest` in the sudoku directory. The program can then be run with `./fuzztest n`, where n is a valid integer argument greater than 0.

Each of the unit test executables can be compiled separately with `make unit_xy`, where `xy` represents the name of the file to be tested (e.g. `unit_create`). Alternatively, `make unit` can be run in the main directory or each of the subdirectories to compile all the unit tests at once.

### Unit tests

We wrote a unit test for each module used by the main program driver. Each of these tests are explained in detail below.

#### create

The unit tests for the `create` module are relatively simple. The unit test calls the `create` function to generate a random puzzle, and then verifies that the board satisfies the requirements by ensuring there are at least 40 empty cells and that the puzzle has exactly one unique solution.

#### solve

The unit tests for solve work by attempting to solve pre-defined puzzles – 3 valid (though extremely difficult) puzzles, an invalid puzzle (one that fails to satisfy the rules of Sudoku from the outset), and an unsolveable puzzle (one for which no valid solution exists). The solver should successfully solve the first 3 puzzles but return an error message on the invalid and unsolveable puzzles.

#### board

The unit tests in this file test each of the functions accessible via the `board` module. Each unit test in this file tests one function – `board_valid`, `board_get`, `board_new`, etc. – and verifies that the expected change is reflected in the board. Note that these test cases may require hitting the enter key on the keyboard a few times to emulate the behavior of `board_scan`.

#### utilities

These unit tests ensure that the functions in the `utilities` module work as intended. Note that there is a very small chance that the `shuffle` unit tests fail if the shuffler by chance leaves the first two values in the array unchanged (that is, it randomly shuffles them back to their original spots). Note that these test cases may take a while to run due to the calls to the `backtrack` function. 

### Fuzz testing

We elected to write our fuzztester in C so that we could directly access the `solve` and `create` functions. The fuzztester works by accepting exactly one command line argument, an integer `n`. If this integer is invalid or not provided, the program exits early and prints an error message. Otherwise, it creates and attempts to solve n boards. Each iteration of the loop creates a board using the `create` function. It then checks that the board is incomplete (that is, has empty spaces to be solved), satisfies the rules of Sudoku, and has exactly one unique solution. Finally, it calls the `solve` function to generate the solution for the board, and verifies that the solution is complete and valid. It repeats this loop n times.