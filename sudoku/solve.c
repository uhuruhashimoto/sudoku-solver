/*
* solve.c - module that scans, solves, and prints a board
* contains a helper function that returns a solved board
*
* 
*/
#include <stdio.h>
#include <stdlib.h>
#include "../common/board.h"
#include "../common/utilities.h"

// solve - scans, solves, and prints board
void solve(board puzzle) 
{
  
  #ifndef UNIT_TEST_SOLVE
    board_scan(puzzle, stdin);
  #endif

  editable_spots_t spots = board_editable_spots(puzzle);
  int num_sol = 0;
  
  if (!backtrack(puzzle, spots, (const int) 1, 0, &num_sol)) {
    fprintf(stderr, "Error: invalid or unsolveable board.\n");
  }
  editable_spots_delete(spots);
}

/** Unit tests **/

#ifdef UNIT_TEST_SOLVE
#include "../common/unittest.h"

//tests
int test_solve(board puzzle, board solution, char *filepath, char *solutionpath);
int test_invalid(board puzzle, char *filepath);
int test_unsolveable(board puzzle, char *filepath);

//helpers
static bool compare_solutions(board a, board b);
static void zero_board(board puzzle);

int main()
{
  board unsolved;
  board solution;
  board invalid;
  board unsolveable;
  int failed = 0;

  zero_board(unsolved);
  zero_board(solution);
  zero_board(invalid);
  zero_board(unsolveable);

  failed += test_solve(unsolved, solution, "test/test1.txt", "test/solution1.txt");
  failed += test_solve(unsolved, solution, "test/test2.txt", "test/solution2.txt");
  failed += test_solve(unsolved, solution, "test/test3.txt", "test/solution3.txt");
  failed += test_invalid(invalid, "test/invalid.txt");
  failed += test_unsolveable(unsolveable, "test/unsolveable.txt");

  if (failed > 0) {
    printf("FAIL %d test cases\n", failed);
    return failed;
  } else {
    printf("PASS all test cases\n");
    return 0;
  }
}

int test_invalid(board puzzle, char *filepath) 
{
  START_TEST_CASE("invalid");
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL) return 1;
  board_scan(puzzle, fp);

  board copy; 
  copy_board(copy, puzzle);
  
  fprintf(stdout, "Testing invalid board:\n");
  solve(puzzle);

  //if backtrack is false, then board is returned in original state
  EXPECT(compare_solutions(puzzle, copy));

  fclose(fp);
  return TEST_RESULT;
}

int test_unsolveable(board puzzle, char *filepath) 
{
  START_TEST_CASE("unsolveable");
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL) return 1;
  board_scan(puzzle, fp);

  board copy; 
  copy_board(copy, puzzle);
  
  fprintf(stdout, "Testing unsolveable board:\n");
  solve(puzzle);

  //if backtrack is false, then board is returned in original state
  EXPECT(compare_solutions(puzzle, copy));

  fclose(fp);
  return TEST_RESULT;
}

int test_solve(board puzzle, board solution, char *filepath, char *solutionpath)
{   
  START_TEST_CASE("solve");
  FILE *fp = fopen(filepath, "r");
  FILE *solfp = fopen(solutionpath, "r");
  if (fp == NULL || solfp == NULL) {
      return 1;
  }
  board_scan(puzzle, fp);
  board_scan(solution, solfp);

  fprintf(stdout, "Input board for solve:\n");
  board_print(puzzle);

  fprintf(stdout, "Generating solution...\n");
  solve(puzzle);

  fprintf(stdout, "TEST SOLUTION:\n");
  board_print(solution);

  EXPECT(compare_solutions(puzzle, solution));

  fclose(fp);
  fclose(solfp);
  return TEST_RESULT;
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