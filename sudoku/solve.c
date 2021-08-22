/*
* solve.c - module that scans, solves, and prints a board
* contains a helper function that returns a solved board
*
* Uhuru
*/
#include <stdio.h>
#include <stdlib.h>
#include "../common/board.h"

// solve - scans, solves, and prints board
void solve(board puzzle) {
    board_scan(puzzle, stdin);

    editable_spots_t spots = board_editable_spots(puzzle);
    int *num_sol = malloc(sizeof(int));
    backtrack(puzzle, spots, (const int) 1, num_sol);
    
    board_print(puzzle);
    free(num_sol);
}

/** Unit tests **/

#ifdef UNIT_TEST_SOLVE
#include <stdio.h>
#include <time.h>
#include "../common/unittest.h"

int test_solve(void);


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

int test_solve(void)
{
  START_TEST_CASE("solve puzzle");

  //solve things here
  
  return TEST_RESULT;
}

#endif // UNIT_TEST_SOLVE