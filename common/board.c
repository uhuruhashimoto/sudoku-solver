/* 
 * board.c
 *
 * Description: the implementation for an API to interact with a board, a 9x9 array of integers
 * 
 * 
 *
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
static bool is_in(int num, int array[9]);
static bool unique_and_valid(int value, int numbers[9], int *index);

/**************** board_initialize ****************/
void board_initialize(board board) 
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0; // set all to 0
        }
    }
}


/**************** board_insert ****************/
void board_insert(board board, int row, int column, int value)
{
    board[row][column] = value;
}


/**************** board_print ****************/
void board_print(board board)
{
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fprintf(stdout, "%d ", board[i][j]);
        }
        if (i < 8) fprintf(stdout, "\n");
    }
}

/**************** board_get ****************/
int board_get(board board, int row, int column)
{
    return board[row][column];
}

// /**************** board_scan ****************/
bool board_scan(board board, FILE* fp)
{
    int i = 0;
    char* row;

    while(i < 9 && (row = freadlinep(fp)) != NULL){

        if(strlen(row) != 18) {
            free(row);
            fprintf(stderr, "not a valid board\n");
            return false;
        }

        int row_arr[9];
        if((sscanf(row, "%d %d %d %d %d %d %d %d %d ", 
            &row_arr[0], &row_arr[1], &row_arr[2], &row_arr[3], &row_arr[4], &row_arr[5], &row_arr[6], &row_arr[7], &row_arr[8]) != 9)) {

            free(row);
            fprintf(stderr, "incorrect format of input. should have 9 numbers with spaces after each number.\n");
            return false;
        }

        else{
            char *value = strtok(row, " ");

            int j = 0;
            while(value != NULL && j < 9){
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
    return true;
}

/**************** board_editable_spots ****************/
editable_spots_t board_editable_spots(board board)
{
    // need variable to keep track of how much space to allocate
    int length = 0;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == 0){
                length++;
            }
        }
    }

    editable_spots_t editable_spots;

    editable_spots.coords = calloc(sizeof(int[2]), length);
    editable_spots.num_spots = length;

    int index = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == 0){ // can edit this spot, is empty
                editable_spots.coords[index][0] = i;
                editable_spots.coords[index][1] = j;
                index++; 
            }
        }
    }
    return editable_spots;
}

/**************** is_valid ****************/
bool is_valid(board board) 
{
    // check rows 
    for (int row = 0; row < 9; row++) {
        int numbers[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int index = 0;
        for (int col = 0; col < 9; col++) {
            if (!unique_and_valid(board[row][col], numbers, &index)) {
                return false;
            }
        }
    }

    // check cols 
    for (int col = 0; col < 9; col++) {
        int numbers[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int index = 0;
        for (int row = 0; row < 9; row++) {
            if (!unique_and_valid(board[row][col], numbers, &index)) {
                return false;
            }
        }
    }

    // check blocks 
    for (int block = 0; block < 9; block++) {
        int row = (block / 3) * 3;
        int col = (block % 3) * 3;
        

        int numbers[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int index = 0;
        for (int i = row; i < row + 3; i++) {
            for (int j = col; j < col + 3; j++) {
                if (!unique_and_valid(board[i][j], numbers, &index)) {
                    return false;
                }
            }
        }
    }

    return true;

}

// returns true if value is not in numbers array and adds value to numbers
// otherwise, returns false and does not add to the array
static bool unique_and_valid(int value, int numbers[9], int *index)
{
    if (value > 9 || value < 0) {
        return false;
    }
    else if (value == 0) {
        return true; // empty cell is always valid 
    }
    else if (is_in(value, numbers)) {
        return false;
    }
    else {
        numbers[*index] = value;
        (*index)++;
    }
    return true;
}

// helper for is_valid
// returns true if num is in array, else false
static bool is_in(int num, int array[9])
{
    for (int i = 0; i < 9; i++) {
        if (array[i] == num) {
            return true;
        }
    }
    return false;
}

/**************** is_complete ****************/
bool is_complete(board board)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    // no spots are empty
    return true;
}


/**************** editable_spots_delete ****************/
void editable_spots_delete(editable_spots_t editable_spots) 
{
    // free allocated space
    // must be called if board_editable_spots is called 
    free(editable_spots.coords);
}


/**************** copy_board ****************/
void copy_board(board original, board copy)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            copy[i][j] = original[i][j];
        }
    }
}


#ifdef UNIT_TEST_BOARD
#include <stdio.h>
#include "unittest.h"


int test_initialize_board(board board);
int test_print_board(board board);
int test_scan_board(board board);
int test_editable_spots(board board);
int test_board_get(board board);
int test_board_valid(board board, char *filepath);
int test_board_complete(board board, char *filepath);


// comment and uncomment tests as needed
int main(){

    board new;


    int failures = 0;
    failures += test_initialize_board(new);
    failures += test_print_board(new);
    failures += test_scan_board(new);
    failures += test_editable_spots(new);
    failures += test_board_get(new);
    failures += test_board_valid(new, "test_board.txt");
    failures += test_board_complete(new, "test_board.txt");
    printf("FAIL %d test cases\n", failures);
    return failures;

}

int test_initialize_board(board board)
{
    START_TEST_CASE("initialize board");
    board_initialize(board);

    EXPECT(board[2][4] == 0);

    END_TEST_CASE;
    return TEST_RESULT;
}

int test_print_board(board board)
{
    START_TEST_CASE("print board");

    board_print(board);

    END_TEST_CASE;
    return TEST_RESULT;
}

int test_scan_board(board board)
{
    START_TEST_CASE("scan board");
    printf("input board from keyboard: \n");
    board_scan(board, stdin);

    board_print(board);
    END_TEST_CASE;
    return TEST_RESULT;
}

int test_editable_spots(board board)
{
    START_TEST_CASE("editable spots");
    FILE *fp = fopen("solvable.txt", "r");
    if (fp == NULL) {
        return 1;
    }
    board_scan(board, fp);

    editable_spots_t editable_spots=board_editable_spots(board);
    for(int i=0; i<editable_spots.num_spots; i++){
        printf("%d, %d ", editable_spots.coords[i][0], editable_spots.coords[i][1]);
        
    }
    EXPECT(editable_spots.coords[4][0] == 0);
    editable_spots_delete(editable_spots);
    END_TEST_CASE;
    return TEST_RESULT;
}

int test_board_get(board board) {
    START_TEST_CASE("board get");

    FILE *fp = fopen("solvable.txt", "r");
    if (fp == NULL) {
        return 1;
    }
    board_scan(board, fp);

    EXPECT(board_get(board, 6, 1) == 4);
    printf("%d\n", board_get(board, 6, 0));
    
    END_TEST_CASE;
    return TEST_RESULT;
}

int test_board_valid(board board, char *filepath) {
    START_TEST_CASE("board valid");
    
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        return 1;
    }
    board_scan(board, fp);
    printf("input board for is_valid:\n");
    board_print(board);

    printf(is_valid(board) ? "is valid\n" : "is invalid\n");
    fclose(fp);
    END_TEST_CASE;
    
    return TEST_RESULT;
}

int test_board_complete(board board, char *filepath) {
    START_TEST_CASE("boardcomplete");
    
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        return 1;
    }
    board_scan(board, fp);
    printf("input board for is_complete:\n");
    board_print(board);
    printf("\n");

    printf(is_complete(board) ? "is complete\n" : "is not complete\n");
    fclose(fp);
    END_TEST_CASE;
    
    return 0;
}

#endif