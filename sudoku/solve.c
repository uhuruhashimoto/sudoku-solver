/*
* solve.c - module that scans, solves, and prints a board
* contains a helper function that returns a solved board
*
* Uhuru
*/
#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void solve();
board *get_solved_board(board *);

// solve - scans, solves, and prints board
void solve() {
    board *unsolved = scan_board(stdin);
    board *solved = get_solved_board(unsolved);
    print_board(solved);
}

// helper - calls backtrack and returns solved board
board *get_solved_board(board *puzzle) {
    editable_spots = get_editable_spots(puzzle);
    int *num_sol = malloc(sizeof(int));
    backtrack(puzzle, editable_spots, (const int) 1, num_sol);
    free(num_sol);
}