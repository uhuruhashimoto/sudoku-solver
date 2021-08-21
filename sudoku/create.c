/*
* create.c - creates a board with greater than 40 empty squares and one unique solution
*
* Kumquat 
* CS 50 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include "../common/board.h"
#include "../common/utilities.h"
#include "solve.h"

//create takes an empty board from main, fills it, and prints it
void create(board board) {
    const int min_removed = 40;
    
    //Fill diagonal quadrants in board 
    fill_diagonals(board);

    //solve board to fill other squares
    solve(board);

    //remove numbers from board
    int *num_removed = malloc(sizeof(int));
    remove_numbers(board, num_removed, min_removed);

    //print board and message
    fprintf(stdout, "NEW BOARD WITH %d NUMBERS REMOVED: \n", *num_removed);
    board_print(board);

    //clean up
    free(num_removed);
}

//recursive loop: removes numbers while maintaining solveable board until the board has >40 empty spots
bool remove_numbers(board board, int *num_removed, const int min_removed) {
    //loop: continue while removed < 40
    if (*num_removed > min_removed) return;
    
    // remove random number
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    int removed = remove_random_number(board, x, y);
        
    // call backtrack to see if puzzle has unique solution
    if (backtrack(board)) {
        // if so, call remove_numbers(board)
        *num_removed++;
        remove_numbers(board, *num_removed, min_removed);
    }

    // if not, put back the number we removed and try a different square
    *num_removed--;
    board_set(board, x, y, removed);
    free(x); free(y);

    return false;
    // If none of the squares removed give a unique solution, backtrack and put back the previous square as well 
}

int remove_random_number(board board, int *x, int *y) {
    //get random coordinates 
    *x = get_random();
    *y = get_random();

    //if board is already empty there, keep looking
    while (board_get(board, x, y) == 0) {
        *x = get_random();
        *y = get_random();
    }

    //if board is not empty, remove a number
    board_insert(board, *x, *y, 0);
}

//returns random int from 1 to 9
static int get_random() {
    return (rand() % 9) + 1;
}
