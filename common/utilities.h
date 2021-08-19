/* 
 * utilities.h - header file for sudoku utilities module
 *
 * CS50
 */

#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <stdio.h>
#include <stdbool.h>

typedef int board[9][9]; // this is temporary until board.h is updated

struct editable_spots { // this is temporary until board.h is updated
  int **coords;
  int num_spots; 
};

bool backtrack(board *board, struct editable_spots spots, const int max_solutions, int cur_index, int *num_solutions);

#endif