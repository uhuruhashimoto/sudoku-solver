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
void board_insert(board* board, int row, int column, int value);

/**************** board_print ****************/
/*
 * 
 * 
 *        
 */
void board_print(board* board);

/**************** board_scan ****************/
/*
 *
 * 
 */
board* board_scan(FILE* fp);


/**************** board_get ****************/
/*
 * 
 * 
 */
void board_get(board* board, int row, int column);

/**************** board_editable_spots ****************/
/*
 * 
 * 
 */
char* board_editable_spots(board* board);

/**************** is_valid ****************/
/*
 * 
 * 
 */
bool is_valid(board* board);


/**************** is_complete ****************/
/*
 * 
 * 
 */
bool is_complete(board* board);


/**************** board_delete ****************/
/* Deletes the board
 * 
 * 
 */
void board_delete(board* board);

#endif // __BOARD_H