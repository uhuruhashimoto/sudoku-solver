/* 
 * board.h - header file for board module
 *
 * Description: 
 * 
 * 
 *
 * CS 50, Team: Kumquat
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

/**************** board_new ****************/
/* creates a new, empty board
 * returns: a pointer to the new board
 * 
 */
board* board_new();

/**************** board_insert ****************/
/* inserts a value into a specifc cell of the board
 *
 * 
 */
void board_insert(board board, int row, int column, int value);

/**************** board_print ****************/
/* prints out a given board
 * 
 *        
 */
void board_print(board board);

/**************** board_scan ****************/
/* scans a board from stdin
 * returns: a pointer to a scanned-in board
 * 
 */
void board_scan(board board, FILE* fp);


/**************** board_get ****************/
/* returns: a value at the cell indicated by
 * row and column value
 * 
 */
int board_get(board board, int row, int column);

/**************** board_editable_spots ****************/
/* returns: an array of coordinates that are editable
 * or marked as "zero"
 * 
 */
editable_spots_t board_editable_spots(board board);

/**************** is_valid ****************/
/* returns: false if the board breaks any rules,
 * true if the board is valid
 * 
 */
bool is_valid(board board);


/**************** is_complete ****************/
/* returns: true if board has all spots filled in,
 * false if still empty spots left
 * 
 */
bool is_complete(board board);


/**************** editable_spots_delete ****************/
/* returns: void 
 * frees space used to store array of coordinates
 * 
 */
void editable_spots_delete(editable_spots_t editable_spots); 


#endif // __BOARD_H