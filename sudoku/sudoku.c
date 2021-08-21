/* 
 * sudoku.c
 *
 * 
 * Usage: ./sudoku [create] [solve]
 *
 * Kumquat
 * CS50 21X
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "solve.h"
#include "create.h"
#include "../common/board.h"

const int ERROR_NUM_ARGS = 1;
const int ERROR_ARG = 2;


int validate_arguments(const int argc, const char *argv[]);


int main(const int argc, const char *argv[])
{
    int validated = validate_arguments(argc, argv);
    if (validated != 0) {
        exit(validated);
    }

    board board;
    board_initialize(board);

    if (strcmp(argv[1], "solve")) {
        solve(board);
    }
    else {
        create(board);
    }

    return 0;
}

int validate_arguments(const int argc, const char *argv[]) 
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./sudoku create or ./sudoku solve");
        return ERROR_NUM_ARGS;
    }
    if (strcmp(argv[1], "create") != 0 && strcmp(argv[1], "solve") != 0) {
        fprintf(stderr, "Argument must be either create or solve");
        return ERROR_ARG;
    }
    return 0;
}

