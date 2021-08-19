# Sudoku DESIGN Spec
## CS50 Group Project 
## Uhuru, Kelly, Megan, Tyler
## NOTE: All team members contributed to this document

# Project Overview:
The **sudoku creator** will create a random 9x9 Sudoku puzzle with a unique solution. The **sudoku solver** will generate a solution to a given puzzle. 

# Data flow:
The ./sudoku executable is our entry point to the whole program. It takes exactly one argument, either “create” or “solve”, and initializes the appropriate module depending on what the user wants to do. For the most part, the only data that really needs to be passed around from module to module is the board struct that keeps track of the state of the puzzle, whether solving or creating. 

For solve: the puzzle to be solved is read from stdin, one line at a time. The puzzle is parsed into a board struct, to which a pointer is then passed to backtrack (and the functions in board.c that backtrack uses) to solve the puzzle. Then, the solve module formats the board (if solvable) to be printed to stdout, or it prints an error message. Note that for solve, we also keep track of a list of “editable” squares (spots that are inputted as 0 when reading the puzzle), to be passed to backtrack as well. 

For create: the puzzle is created as a board struct first. It is initialized to empty, then the diagonals are filled in. Then the board is passed to solve, and then random numbers are deleted from the completed board until a puzzle with a unique solution is found. The method to check for a unique solution leverages backtrack. Backtrack, and all other helper functions in the creation process, take a pointer to the board struct as one of their parameters. Finally, the create module prints the puzzle to stdout. 

# User interface: 
The sudoku’s interface with the user is on the command line; it must always have two arguments. The user can call:

EITHER
```
./sudoku create
```

OR
```
./sudoku solve
```

# Inputs/outputs:
Input: the only inputs for `sudoku create` are command-line parameters; see the User Interface section above. The `sudoku solve` will also read in an unsolved puzzle from stdin.

Output for `sudoku create`: A unique and randomized puzzle with at least 40 missing numbers.

Output for `sudoku solve`: The solution for a given, unfinished puzzle.


# Functional Decomposition:
We anticipate the following modules and functions: 

sudoku, the driver program that calls both create and solve 
    main
    validate_arguments 

create, the module for creating a puzzle with a unique solution

solve, the module for solving a puzzle inputted through stdin

common, the directory (can be compiled to a library) of common functionality needed for both create and solve 
    board.c, providing an API to interact with a board struct  
    board struct: a wrapper (typedef) for a 9x9 array of ints 
    isvalid 
	iscomplete 
	insert
	delete
	print
	scan 
	get

utilities.c, providing functions that are needed in the puzzle creation and solving process
	backtrack
	filldiagonals
	removerandom

# Pseudocode
*Note: we chose a brute-force approach to solving, using the backtracking method outlined in https://en.wikipedia.org/wiki/Sudoku_solving_algorithms 
https://dlbeer.co.nz/articles/sudoku.html. Both our backtrack and solve algorithms use a recursive approach.*

## Backtrack
Inputs: board ptr, array of editable_spots, const int max solutions, pointer # solutions
Returns: bool

	- if index > length editable_spots return false;
	- for i from 1..9
		- put i in board 
		- is valid? 
			- if is complete, solution found! 
				- increment # solutions
				- if hit max solutions, return true
			- do backtrace(board, array, max, # solutions ++)
				- returns true? return true;
				- returns false? return false
	- remove i from board;
	- return false //this catches an unsolveable board



## Create
Inputs: none
Returns: board with >=40 empty spots and one unique solution

	- Fill diagonal quadrants
		- Scramble a 1x9 array, and insert it into corner, middle, and corner of board
	- Solve board
		- call solve() on board to return a fully solved board
	- Remove numbers from solved board
		- this is basically backtrack (same recursive structure)















