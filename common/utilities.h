/* 
 * utilities.h - header file for sudoku utilities module
 *
 * 
 */

#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <stdio.h>
#include <stdbool.h>
#include "board.h"

bool backtrack(board board, editable_spots_t editable_spots, const int max_solutions, int cur_index, int *num_solutions);

void fill_diagonals(board board);

void remove_random_cell(board board);

void shuffle_arr(int *arr, int n);

void shuffle_arr_twod(int arr[][2], int n);

#endif