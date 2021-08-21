# Sudoku DESIGN Spec
#### CS50 Group Project 
#### Uhuru, Kelly, Megan, Tyler
#### NOTE: All team members contributed to this document


### Project Overview:
The **sudoku creator** will create a random 9x9 Sudoku puzzle with a unique solution. The **sudoku solver** will generate a solution to a given puzzle. 

A Design Spec should contain several sections:

* User interface
* Inputs and Outputs
* Functional decomposition into modules
* Pseudo code for logic/algorithmic flow
* Dataflow through modules
* Major data structures
* Testing plan

Let's look through each.


### User interface

The sudoku’s interface with the user is on the command line; it must always have two arguments. The user can call:

EITHER
```
./sudoku create
```

OR
```
./sudoku solve
```


### Inputs and outputs

Input: the only inputs for `sudoku create` are command-line parameters; see the User Interface section above. The `sudoku solve` will also read in an unsolved puzzle from stdin.

Output for `sudoku create`: A unique and randomized puzzle with at least 40 missing numbers.

Output for `sudoku solve`: The solution for a given, unfinished puzzle.


### Functional decomposition into modules

We anticipate the following modules and functions: 

1. *sudoku* - the driver program that calls both create and solve 
	* main() - contains board struct: a wrapper (typedef) for a 9x9 array of ints 
	* validate_arguments()

2. *create* - the module for creating a puzzle with a unique solution

3. *solve* - the module for solving a puzzle inputted through stdin

4. *common* - the directory (can be compiled to a library) of common functionality needed for both create and solve 
	* board.c - providing an API to interact with a board struct (initialized in driver)
	* isvalid()
	* iscomplete()
	* board_insert()
	* board_print()
	* board_scan() 
	* board_get()
    * board_editable_spots()
    * editable_spots_delete()

5. *utilities.c* providing functions that are needed in the puzzle creation and solving process
	* backtrack()
	* filldiagonals()
	* removerandom()


### Pseudo code for logic/algorithmic flow
*Note*: we chose a brute-force approach to solving, using the backtracking method outlined in https://en.wikipedia.org/wiki/Sudoku_solving_algorithms 
https://dlbeer.co.nz/articles/sudoku.html. Both our backtrack and solve algorithms use a recursive approach.*

#### Solve: Backtrack
Inputs (for backtrack): board ptr, array of editable_spots, const int max solutions, pointer # solutions
Returns: bool

1. check for editable spots
2. loop through possible sudoku values 1..9
	- put the current value in to the board; check if valid
        - Check if the board is complete
            - if so, solution is found; return true
            - if not complete, continue backtracking

#### Create
Inputs: none
Returns: board with >=40 empty spots and one unique solution

1. Fill diagonal blocks
    - Scramble a 1x9 array, and insert it into the 3x3 arrays at the top left corner, middle, and bottom right corner of board
2. Solve board
    - call solve() on board to return a fully solved board
3. While we’ve removed fewer than 40 numbers: 
4. Remove numbers from solved board at random 
        - Call backtrack to see if there is a unique solution to the puzzle now that another number has been removed
        - If so, continue to remove numbers, if not, put back the number we just removed and try a different random square to remove 
        - If none of the squares removed give a unique solution, backtrack and put back the previous square as well 
    - this is basically backtrack (same recursive structure)


### Data flow:
The ./sudoku executable is our entry point to the whole program. It takes exactly one argument, either “create” or “solve”, and initializes the appropriate module depending on what the user wants to do. For the most part, the only data that really needs to be passed around from module to module is the board that keeps track of the state of the puzzle, whether solving or creating. This board is a 9x9 array of integers, intialized in our main() driver, and persists while our driver runs. 

For solve: the puzzle to be solved is read from stdin, one line at a time. The puzzle is parsed into our (statically allocated) array, to which a pointer is then passed to backtrack (and the functions in board.c that backtrack uses) to solve the puzzle. Then, the solve module formats the board (if solvable) to be printed to stdout, or it prints an error message. Note that for solve, we also keep track of a list of “editable” squares (spots that are inputted as 0 when reading the puzzle), to be passed to backtrack as well. 

For create: the puzzle is created as a board first. It is initialized to contain zeros, and then the diagonals are filled in. Then the board is passed to solve, and then random numbers are deleted from the completed board until a puzzle with a unique solution is found. The method to check for a unique solution leverages backtrack. Backtrack, and all other helper functions in the creation process, take a pointer to the board struct as one of their parameters. Finally, the create module prints the puzzle to stdout. 


### Major data structures

```
typedef int board[9][9];
```

```
typedef struct editable_spots {
  int (*coords)[2];
  int num_spots; 
} editable_spots_t;
```


### Testing plan
We plan on implementing two primary types of testing:

*Unit Testing*.
We plan on unit testing both the creator and solver modules. For the creator module, this can be accomplished by generating puzzles and verifying that at least 40 cells are unfilled, that the grid is a valid Sudoku grid, etc. We can also individually unit test components of the creator module, such as generating a puzzle with the diagonals filled in. For the solver module, the unit testing will primarily be of the backtrack function. Since the backtrack function doesn’t rely on random input, we can check its output against the expected values for several predefined values. 

*Fuzz Testing*.
Fuzz testing can be used to test both the creator and the solver. We can randomly generate n puzzles and verify both that the created puzzles and completed solutions yield a valid Sudoku grid (no duplicates in rows, columns, or 3x3 quadrants). 
















