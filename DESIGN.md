# DESIGN Doc
## CS50 Group Project 
## Uhuru, Kelly, Megan, Tyler
## NOTE: All team members contributed to this document

# Initial ideas

# CREATING MODULE

Make a 9x9 of random numbers, and then remove numbers in pairs (randomly).

After each removal, check if puzzle can be solved. 
- Run your solver on the puzzle, and have it keep backtracking and return ALL solutions.
- If there is more than one solution, put the numbers back in and try again.
- If there is one solution, take out more numbers (until we have >40 removed)


# SOLVING MODULE

How to Solve: Backtracking: if move is made, and option is the last possible option (max), and grid is not valid, then we go back a move and increment it (because we know that the last move is wrong.)

Backtrack Recursion Pseudocode

recursive helper(board, array of editable spots, index):
    if index > length of array of editable spots: 
        return 
    for i in range 1-9:
         put i in array[index] 
         is that valid?
            if yes: recurse(board, array of editable spots, index + 1)
is the board complete? 
    return

## MODULAR DESIGN

two directories: common, sudoku, and libcs50, each w/ sep makefile
common: board.c, utilities.c (backtrack.c, helper functions for 3d array) 
sudoku: solve.c, create.c, sudoku.c (driver)

struct: 
typedef int[9][9] board; 
board[x][y]

## board.c: 
overview: contains a struct (9x9 array)
functions: 
board_new(): returns pointer to 
board_insert(board, row, col, number): 
board_delete(board):
board_print(board):
board_scan(FILE fp):
board_get(board, row, col): 
board_editable_spots(board): returns array of coordinates that are zero (called once, after scan/create)
is_valid(board): returns bool representing if the board breaks any rules in its current state 
is_complete(board): returns if board has all spots filled in (board is allowed to be non-valid)


## solve.c: 
overview:
functions:
board_scan()
board_editable_spots()
backtrack w/ custom stop function
custom stop function(void ptr arg): stop if board is complete and is valid. returns bool 

## create.c:
overview:
functions:

## utilities.c: 
overview: 
functions: 
backtrack(board, array of editable spots, int max_num_solutions, int ptr num_solutions_found): returns board, NULL if not solvable 





