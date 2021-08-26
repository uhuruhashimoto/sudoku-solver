/* 
 * board.h - header file for board module
 *
 * Description: the interface for an API to interact with a board, a 9x9 array of integers
 * 
 * 
 */

#ifndef __BOARD_H
#define __BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/**************** global types ****************/
typedef int board[9][9];

typedef struct editable_spots {
  int (*coords)[2];
  int num_spots; 
} editable_spots_t;

/**************** board_initialize ****************/
/* returns void
 * 
 * sets all elements in the board to 0 
 */
void board_initialize(board board);

/**************** board_insert ****************/
/* returns void 
 * 
 * sets an element at the given 
 * row, col location to the given value
 */
void board_insert(board board, int row, int column, int value);

/**************** board_print ****************/
/* returns void 
 *
 * prints a given board
 * to stdout in the format of 
 * 9 numbers per line, with a space between 
 * each
 */
void board_print(board board);

/**************** board_scan ****************/
/* returns void
 * 
 * scans 9 lines of input (or until EOF) from 
 * stdin and reads them into the given board struct.
 * expects input of the form 9 numbers per line, 
 * separated by a single space. 
 * 
 */
bool board_scan(board board, FILE* fp);


/**************** board_get ****************/
/* returns: a value at the cell indicated by
 * row and column value
 * 
 * expects: row and column are in bounds for the 9x9 array
 */
int board_get(board board, int row, int column);

/**************** board_editable_spots ****************/
/* returns: an array of coordinates that are editable
 * (marked as "zero" in the board)
 * 
 * caller is responsible for later calling 
 * ediable_spots_delete()
 */
editable_spots_t board_editable_spots(board board);

/**************** is_valid ****************/
/* returns: false if the board breaks any rules,
 * true if the board is valid
 *
 * rules include: all numbers are from 1-9, 
 * no number can appear more than once in any row,
 * column, or 3x3 block
 */
bool is_valid(board board);


/**************** is_complete ****************/
/* returns: true if board has all spots filled in,
 * false if still empty spots left
 * 
 * empty spots are defined by a zero 
 */
bool is_complete(board board);


/**************** editable_spots_delete ****************/
/* returns: void 
 * frees space used to store array of coordinates
 * 
 */
void editable_spots_delete(editable_spots_t editable_spots); 

/**************** copy_board ****************/
/* returns: void 
 * copies a board from original to copy
 * 
 */
void copy_board(board original, board copy);

#endif // __BOARD_H