# Sudoku Implementation
## CS50 Summer 2021

### Algorithm / Pseudocode for Main Modules

##### Main()
1. Check input arguments
2. Call either solve() or create()

#### Solve()
1. Initialize a `editable_spots_t` struct to keep track of cells withe value 0

2. *scanBoard()* - scan in a 9x9 board from stdin
- Read in the unsolved puzzle from stdin
    - Validate board input (make sure 9x9)
    - Read each line using freadlinep
        - For each line, tokenize (strtok) and tread in individual values
        - Convert char* value to an int (atoi)
        - Set each integer value to a coordinate of the board
- Return int board[9][9] when complete

3. *backtrack()* - fill in empty spots valid numbers 1..9
- If index >= length (editable_spots) return false;
	- For i from 1..9
		- Put i in board 
		- Check if valid
			- If is complete, solution found! 
				- Increment # solutions
				- If hit max solutions, return true
			- Call backtrack(board, array, max, # solutions ++)
				- returns true? return true;
	- Remove i from the current spot and return false


#### Create()
1. *board_initialize()* - Initialize a 9x9 board and set all its cells to 0

2. *fill_diagonals()* - Randomly fill in diagonal 3x3 matrices with values 1..9
    - Initialize an array of values 1-9
    - Shuffle the array randomly
    - For each quadrant... loop through its coordinates
        - Set each cell with a value from the array of values
        - Incrememnt the index of the array of values for the next cell

3. *backtrack()* - "solve" the board by filling in the rest of the empty cells with the same backtrack algorithm detailed in the solve module

4. *remove_spots()* - remove 40 numbers from the board to create a solveable board with a unique solutions
    - Loop through all 81 cells on the board
        - If the cell's value has not been removed (set to 0)...
            - Store the cell's coordinate and its value into an array
            - Remove the the cell with board_insert() to insert 0 at that spot
            - Check if the board has a unique solution with the removed spot by calling *backtrack()*
                - If the board has a unique solution and has not removed enough spots, continue to remove numbers
                - If the board is not unique, restore the cell to its original value and remove a new cell
                - If none of the removed cells produce a unique solution, backtrack again and put back the previous square
            - Return True if successfully removes 40 values and board has unique solution
    - Return False if unsuccessful at removing spots



### Main Data Structures

#### board
A 9x9 array to represent a Sudoku board.

```c
typedef int board[9][9];
```

#### editable_spots_t
A struct that holds the coordinates and a count of the number of editable spots.

```c
typedef struct editable_spots {
  int (*coords)[2];
  int num_spots; 
} editable_spots_t;
```

#### spots_t
A struct that holds the coordinates & value of removed spots as well as a count of the number of removed spots.

```c
typedef struct spots {
  int coords[81][3];
  int num_spots; 
} spots_t;
```
