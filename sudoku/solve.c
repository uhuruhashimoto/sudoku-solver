/*
* solve.c - module that scans, solves, and prints a board
* contains a helper function that returns a solved board
*
* Uhuru
*/
#include <stdio.h>
#include <stdlib.h>
#include "../common/board.h"
#include "../common/utilities.h"

// solve - scans, solves, and prints board
void solve(board puzzle) {
    board_scan(puzzle, stdin);

    editable_spots_t spots = board_editable_spots(puzzle);
    int *num_sol = malloc(sizeof(int));
    backtrack(puzzle, spots, (const int) 1, 0, num_sol);
    
    board_print(puzzle);
    free(num_sol);
}

/** Unit tests **/

#ifdef UNIT_TEST_SOLVE
#include "../common/unittest.h"

//tests
int test_solve(board puzzle, board sol, char *filepath, char *solutionpath);

//helpers
static bool compare_solutions(board a, board b);
static void zero_board(board puzzle);


int main()
{
  board unsolved;
  board solution;
  int failed = 0;

  zero_board(unsolved);
  zero_board(solution);

  failed += test_solve(unsolved, solution, "test.txt", "solution.txt");

  if (failed > 0) {
    printf("FAIL %d test cases\n", failed);
    return failed;
  } else {
    printf("PASS all test cases\n");
    return 0;
  }
}

int test_solve(board puzzle, board solution, char *filepath, char *solutionpath)
{   
  FILE *fp = fopen(filepath, "r");
  FILE *solfp = fopen(solutionpath, "r");
  if (fp == NULL || solfp == NULL) {
      return 1;
  }
  board_scan(puzzle, fp);
  board_scan(solution, solfp);

  fprintf(stdout, "input board for solve:\n");
  board_print(puzzle);

  solve(puzzle);

  fprintf(stdout, "SOLUTION:\n");
  board_print(solution);

  fprintf(stdout, "solved board:\n");
  board_print(puzzle);

  if (!compare_solutions(puzzle, solution)) {
    fclose(fp);
    fclose(solfp);
    return 1;
  }
  
  fclose(fp);
  fclose(solfp);
  return 0;
}

static void zero_board(board puzzle) {
  for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
          puzzle[i][j] = 0;
      }
  }
}

static bool compare_solutions(board a, board b) 
{
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
        if (a[i][j] != b[i][j]) return false;
    }
  }
  return true;
}

#endif // UNIT_TEST_SOLVE