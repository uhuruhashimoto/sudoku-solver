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

void create(board board) {
    //initialize data structures
    board_initialize(board);
    editable_spots_t spots = board_editable_spots(board);
    int num_solutions = 0;

    //fill diagonals
    fill_diagonals(board);
    
    //solve
    backtrack(board, spots, 1, 0, &num_solutions);

    //initialize data structures for recursive loop
    //create and shuffle to_remove (all slots in board)
    int to_remove[81][2];
    initialize_to_remove(to_remove);
    shuffle_arr(to_remove, 81);
    //initialize removed
    spots_t removed;

    //create board recursively
    remove_spots(board, to_remove, removed);

    //print board
    board_print(board);
}

static bool already_removed(int spot[2], spots_t removed);

//recursive helper for board creation (backtrack equivalent)
bool remove_spots(board board, int to_remove[81][2], spots_t removed) {
    if (removed.num_spots >= 40) {
        return false;
    }

    // look through every spot in board
    for (int i = 0; i < 81; i++) {
        int spot[2] = to_remove[i];
        // if it hasn't been removed, remove it and check for unique solutions
        if (!already_removed(spot, removed)) {
            // store coords and val in removed
            removed.num_spots++;
            int length = removed.num_spots;
            removed.coords[length - 1][0] = spot[0];
            removed.coords[length - 1][1] = spot[1];
            removed.coords[length - 1][2] = board_get(board, spot[0], spot[1]);
            //remove spot
            board_insert(board, spot[0], spot[1], 0);
            //check if board has unique solution
            int num_solutions = 0;
            backtrack(board, board_editable_spots(board), 1, 0, &num_solutions);
            if (num_solutions == 1) { // unique solution
                if (removed.num_spots >= 40) return true; // stop recursing
                if (remove_spots(board, to_remove, removed)) return true;
            } 
            // put it back
            else {
                board_insert(board, spot[0], spot[1], removed.coords[length - 1][2]);
                removed.coords[length - 1][0] = 0;
                removed.coords[length - 1][1] = 0;
                removed.coords[length - 1][2] = 0;
                removed.num_spots--;
            } 
        }
        else { // already removed, try next spot 
            continue;
        }
    }
    //return false
    return false;
}


static bool already_removed(int spot[2], spots_t removed)
{
    for (int i = 0; i < removed.num_spots; i++) {
        if (removed.coords[i][0] == spot[0] && removed.coords[i][1] == spot[1]) {
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
