/*
* create.c - creates a board with greater than 40 empty squares and one unique solution
*
* Kumquat 
* CS 50 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include "../common/board.h"
#include "../common/utilities.h"
#include "solve.h"

typedef struct spots {
  int coords[81][3];
  int num_spots; 
} spots_t;

/****** STATIC HELPERS ******/
static bool already_removed(int x, int y, spots_t removed);
static void initialize_to_remove(int to_remove[81][2]);
static bool remove_spots(board board, int to_remove[81][2], spots_t removed);

void create(board board) {
    //initialize data structures
    board_initialize(board);
    
    int num_solutions = 0;

    //fill diagonals
    fill_diagonals(board);
    editable_spots_t spots = board_editable_spots(board);
    
    //solve
    backtrack(board, spots, 1, 0, &num_solutions);
    editable_spots_delete(spots);

    //initialize data structures for recursive loop
    //create and shuffle to_remove (all slots in board)
    int to_remove[81][2];
    initialize_to_remove(to_remove);
    shuffle_arr_twod(to_remove, 81);
    //initialize removed
    spots_t removed;
    removed.num_spots = 0;

    //create board recursively
    remove_spots(board, to_remove, removed);

    //print boardstat
    board_print(board);
}


//recursive helper for board creation (backtrack equivalent)
static bool remove_spots(board puzzle, int to_remove[81][2], spots_t removed)
{
    if (removed.num_spots >= 41) {
        return false;
    }

    // look through every spot in board
    for (int i = 0; i < 81; i++) {
        int x = to_remove[i][0];
        int y = to_remove[i][1];
        // if it hasn't been removed, remove it and check for unique solutions
        if (!already_removed(x, y, removed)) {
            // store coords and val in removed
            removed.num_spots++;
            int length = removed.num_spots;
            removed.coords[length - 1][0] = x;
            removed.coords[length - 1][1] = y;
            removed.coords[length - 1][2] = board_get(puzzle, x, y);
            //remove spot
            board_insert(puzzle, x, y, 0);
            //check if board has unique solution
            int num_solutions = 0;
            board copy;
            copy_board(puzzle, copy);
            editable_spots_t spots = board_editable_spots(puzzle);
            backtrack(copy, spots, 2, 0, &num_solutions);
            editable_spots_delete(spots);
            if (num_solutions == 1) { // unique solution
                if (removed.num_spots >= 41) return true; // stop recursing
                if (remove_spots(puzzle, to_remove, removed)) return true;
            } 
            // put it back

            board_insert(puzzle, x, y, removed.coords[length - 1][2]);
            removed.coords[length - 1][0] = 0;
            removed.coords[length - 1][1] = 0;
            removed.coords[length - 1][2] = 0;
            removed.num_spots--;

        }
        else { // already removed, try next spot 
            continue;
        }
    }
    //return false
    return false;
}


static bool already_removed(int x, int y, spots_t removed)
{
    for (int i = 0; i < removed.num_spots; i++) {
        if (removed.coords[i][0] == x && removed.coords[i][1] == y) {
            return true;
        }
    }
    return false;
}

static void initialize_to_remove(int to_remove[81][2])
{
    int index = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            to_remove[index][0] = i;
            to_remove[index][1] = j;
            index++;
        }
    }
}


/** Unit tests **/

#ifdef UNIT_TEST_CREATE
#include <stdio.h>
#include <time.h>
#include "../common/unittest.h"

int test_create(void);
//helpers
static bool meets_parameters(board puzzle);
static bool has_one_solution(board puzzle);

int main()
{
  srand ( time(NULL) );
  int failed = 0;
  failed += test_create();

  if (failed) {
    printf("FAIL %d test cases\n", failed);
    return failed;
  } else {
    printf("PASS all test cases\n");
    return 0;
  }
}

int test_create(void)
{
  START_TEST_CASE("create puzzle");

  board puzzle;
  create(puzzle);

  EXPECT(meets_parameters(puzzle));
  EXPECT(has_one_solution(puzzle));
  
  return TEST_RESULT;
}

// integers 1-9; 40+ zeroes
static bool meets_parameters(board puzzle) 
{
    int zero_count = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (puzzle[i][j] == 0) zero_count++;
            if (puzzle[i][j] > 9 || puzzle[i][j] < 0) return false;
        }
    }

    if (zero_count < 40) return false;
    return true;
}

static bool has_one_solution(board puzzle) 
{
    editable_spots_t spots = board_editable_spots(puzzle);
    int num_sol = 0;
    backtrack(puzzle, spots, (const int) 2, 0, &num_sol);
    editable_spots_delete(spots);
    if (num_sol != 1) return false;
    return true;
}

#endif // UNIT_TEST_CREATE
