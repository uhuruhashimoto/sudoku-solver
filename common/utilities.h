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


/**************** backtrack ****************/
/* Repeatedly try combinations of values in the empty spots of a 
 * board and check if the board is solved until no solution is found
 * or the max number of solutions is hit
 *
 * We return:
 *   true if we find max_solutions number of solutions,
 *   false otherwise
 * 
 * Caller is responsible for:
 *   initializing board with board_initialize first,
 *   setting cur_index to 0 at first, and passing in
 *   a pointer to an int that is initially 0
 */
bool backtrack(board board, 
                editable_spots_t editable_spots,
                const int max_solutions,
                int cur_index,
                int *num_solutions);

/**************** fill_diagonals ****************/
/* Given an initialized board, fill in the top left,
 * middle, and bottom right blocks of the board with
 * random values 1-9
 *
 * We return: 
 *  void, but board is now a (valid) board with the 
 *  correct blocks filled in witth random values
 * 
 * 
 * Caller is responsible for:
 *  calling board_initialize first, and seeding the 
 *  random generation
 */
void fill_diagonals(board board);

/**************** shuffle_arr ****************/
/* Given an integer array and its length, shuffle 
 * its elements to a random order
 *
 * We return: 
 *  void, but the elements of the array are now 
 *  shuffled into a random order
 * 
 * Caller is responsible for:
 *  correctly calculating the length of the array, 
 *  and setting the seed for the random functions
 */
void shuffle_arr(int *arr, int n);

/**************** shuffle_arr_twod ****************/
/* Given an array of length two integer arrays,
 * and the length of the outer array, shuffle 
 * the two-element arrays randomly
 *
 * We return: 
 *  void, but the elements (arrays) of the array are now 
 *  shuffled into a random order
 * 
 * Caller is responsible for:
 *  correctly calculating the length of the array, 
 *  and setting the seed for the random functions
 */
void shuffle_arr_twod(int arr[][2], int n);

#endif