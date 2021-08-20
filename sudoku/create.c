/*
* create.c - creates a board with greater than 40 empty squares and one unique solution
*
* Kumquat 
* CS 50 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include "../common/board.h"

void create() {
    //declare board
    
    //Fill diagonals (3)
    //solve board to fill other squares
    //remove numbers from board

    //print board and message

}

//recursive loop: removes numbers while maintaining solveable board until the board has >40 empty spots
bool remove_numbers(board *board, int num_removed) {
    //loop: while removed < 40
        // remove random number
        // call backtrack to see if puzzle has unique solution
        // if so, call remove_numbers(board)
        // if not, put back the number we removed and try a different square
        // If none of the squares removed give a unique solution, backtrack and put back the previous square as well 
}

void fill_diagonals(board *board) {
    //scramble a 9x9 array and put it into the board diagonals
}