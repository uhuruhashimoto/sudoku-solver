/* 
 * board.c
 *
 * Description: 
 * 
 * 
 *
 * CS 50, Team: Kumquat
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "board.h"
#include "file.h"


/************* Data Structs *************/
typedef int board[9][9];

typedef struct editable_spots {
  int **coords;
  int num_spots; 
} editable_spots_t;



/********** Function Prototypes ************/

/**************** board_new ****************/
board* board_new() {
    board *new = malloc(sizeof(int[9][9]));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            *new[i][j] = 0;
        }
    }
	return new;
}


/**************** board_insert ****************/
void board_insert(board board, int row, int column, int value){
    board[row][column] = value;
}


/**************** board_print ****************/
void board_print(board board){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fprintf(stdout, "%d ", board[i][j]);
        }
        fprintf(stdout, "\n");
    }
}


// /**************** board_scan ****************/
void board_scan(board board, FILE* fp){
    int i=0;
    char* row;
    board_print(board);

    while((row = freadlinep(fp))!=NULL && i < 9){


        // if(sscanf("%d %d %d %d %d %d %d %d %d\n", &row[0], &row[1], &row[2], &row[3], &row[4], &row[5], &row[6], &row[7], &row[8]) != 9){
        // printf("sudoku board must have 9x9 dimensions, please re-enter a valid board.");
        // return 1;
        // }

        if(strlen(row) != 18){
            free(row);
            fprintf(stderr, "not a valid board");
            return;
        }

        else{

            char *value = strtok(row, " ");

            int j = 0;
            while(value!=NULL && j < 9){
                int val;
                sscanf(value, "%d", &val);
                board[i][j] = val;

                j++;

                board_print(board);

                value = strtok(NULL, " ");
            }
            i++;
            free(row);

        }
    }
}

// void board_delete(board *to_delete) 
// {
//     free(to_delete);
// }

#ifdef UNIT_TEST
#include <stdio.h>
#include "unittest.h"

int test_new_board(board board);
int test_print_board(board board);
int test_scan_board(board board);

int main(){
    board new;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            new[i][j] = 0;
        }
    }
    int failures = 0;
    failures += test_new_board(new);
    failures += test_print_board(new);
    failures += test_scan_board(new);
    printf("FAIL %d test cases\n", failures);
    return failures;

}

int test_new_board(board board)
{
    // START_TEST_CASE("newboard");
    // board* new = board_new();

    // EXPECT(new != NULL);

    // END_TEST_CASE;
    return 0;
}

int test_print_board(board board)
{
    START_TEST_CASE("printboard");

    board_print(board);

    END_TEST_CASE;
    return 0;
}

int test_scan_board(board board)
{
    START_TEST_CASE("scanboard");
    board_scan(board, stdin);

    board_print(board);
    END_TEST_CASE;
    return 0;
}

#endif