/*
* solve.c - module that scans, solves, and prints a board
* contains a helper function that returns a solved board
*
* Uhuru
*/
#include <stdio.h>
#include <stdlib.h>
#include "board.h"

// solve - scans, solves, and prints board
void solve(board puzzle) {
    board_scan(puzzle, stdin);

    editable_spots_t spots = board_editable_spots(puzzle);
    int *num_sol = malloc(sizeof(int));
    backtrack(puzzle, spots, (const int) 1, num_sol);
    
    board_print(puzzle);
    free(num_sol);
}