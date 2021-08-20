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

/**************** board_get ****************/
int board_get(board board, int row, int column){
    return board[row][column];
}

// /**************** board_scan ****************/
void board_scan(board board, FILE* fp){
    int i=0;
    char* row;

    while((row = freadlinep(fp))!=NULL && i < 9){

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

                value = strtok(NULL, " ");
            }
            i++;
            free(row);

        }
    }
}

/**************** board_editable_spots ****************/
editable_spots_t board_editable_spots(board board){
    int length=0;

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(board[i][j]==0){
                length++;
            }
        }
    }

    editable_spots_t editable_spots;

    editable_spots.coords = calloc(sizeof(int[2]), length);

    editable_spots.num_spots = length;

    int index=0;
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(board[i][j]==0){
                
                editable_spots.coords[index][0] = i;
                editable_spots.coords[index][1] = j;
                index++; 
            }
        }
    }
    return editable_spots;
}





#ifdef UNIT_TEST
#include <stdio.h>
#include "unittest.h"

int test_new_board(board board);
int test_print_board(board board);
int test_scan_board(board board);
int test_editable_spots(board board);
int test_board_get(board board);


int main(){
    board new;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            new[i][j] = 0;
        }
    }
    int failures = 0;
    // failures += test_new_board(new);
    // failures += test_print_board(new);
    // failures += test_scan_board(new);
    // failures += test_editable_spots(new);
    failures += test_board_get(new);
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

int test_editable_spots(board board)
{
    START_TEST_CASE("editable spots");
    board_scan(board, stdin);


    editable_spots_t editable_spots=board_editable_spots(board);
    for(int i=0; i<editable_spots.num_spots; i++){
        printf("%d, %d ", editable_spots.coords[i][0], editable_spots.coords[i][1]);
        
    }
    
    END_TEST_CASE;
    return 0;
}

int test_board_get(board board) {
    START_TEST_CASE("boardget");
    printf("input board for board_get:\n");
    board_scan(board, stdin);

    printf("%d\n", board_get(board, 6, 0));
    
    END_TEST_CASE;
    return 0;
}

#endif