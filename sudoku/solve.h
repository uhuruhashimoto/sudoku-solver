/* 
 * solve.h - header file for solve module
 *
 * Description: 
 * 
 * 
 *
 * CS 50, Team: Kumquat
 */

#ifndef __SOLVE_H
#define __SOLVE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../common/board.h"


/**************** solve ****************/
/* Given an initialized board, 
 * solve the board if possible and print it 
 * to stdout 
 * 
 * We return: 
 *  true if the board was solved, false if 
 *  board was invalid or not solvable 
 * 
 * Caller is responsible for:
 *  calling board_initialize before passing board 
 *  
 */
bool solve(board board);


#endif // __SOLVE_H