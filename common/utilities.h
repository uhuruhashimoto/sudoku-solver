/* 
 * utilities.h - header file for sudoku utilities module
 *
 * CS50
 */

#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <stdio.h>
#include <stdbool.h>
#include "board.h"

bool backtrack(board board, editable_spots_t editable_spots, const int max_solutions, int cur_index, int *num_solutions);

void fill_diagonals(board board);

void remove_random_cell(board board);

#endif