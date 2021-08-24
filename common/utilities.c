/* 
 * utilities.c - CS50 'utilities' module
 *
 * see utilities.h for more information.
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include "board.h"

void shuffle_arr(int *arr, int n)
{
  int i, j, temp;
  for (i = n - 1; i > 0; i--) {
    j = rand() % (i + 1);
    temp = arr[j];
    arr[j] = arr[i];
    arr[i] = temp;
  }
}

void shuffle_arr_twod(int arr[][2], int n)
{
  int i, j, temp_x, temp_y;
  for (i = n - 1; i > 0; i--) {
    j = rand() % (i + 1);
    temp_x = arr[j][0];
    temp_y = arr[j][1];

    arr[j][0] = arr[i][0];
    arr[j][1] = arr[i][1];

    arr[i][0] = temp_x;
    arr[i][1] = temp_y;
  }
}

void fill_diagonals(board board)
{
  // quadrant 1
  int quad_one[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  shuffle_arr(quad_one, 9);
  int i = 0;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      board_insert(board, x, y, quad_one[i]);
      i++;
    }
  }

  // quadrant 2
  int quad_two[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  shuffle_arr(quad_two, 9);
  i = 0;
  for (int x = 3; x < 6; x++) {
    for (int y = 3; y < 6; y++) {
      board_insert(board, x, y, quad_two[i]);
      i++;
    }
  }

  // quadrant 3
  int quad_three[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  shuffle_arr(quad_three, 9);
  i = 0;
  for (int x = 6; x < 9; x++) {
    for (int y = 6; y < 9; y++) {
      board_insert(board, x, y, quad_three[i]);
      i++;
    }
  }
}

bool backtrack(board board, editable_spots_t editable_spots, const int max_solutions, int cur_index, int *num_solutions)
{
  if (cur_index >= editable_spots.num_spots) {
    return false;
  }

  for (int i = 1; i <= 9; i++) {
    board_insert(board, editable_spots.coords[cur_index][0], editable_spots.coords[cur_index][1], i);
    if (is_valid(board)) {
      if (is_complete(board)) {
        (*num_solutions)++;
        if (*num_solutions >= max_solutions) {
          return true;
        }
      }
      if (backtrack(board, editable_spots, max_solutions, cur_index + 1, num_solutions)) {
        return true;
      }
    }
  }

  board_insert(board, editable_spots.coords[cur_index][0], editable_spots.coords[cur_index][1], 0);
  return false;
}

/** Unit tests **/
#ifdef UNIT_TEST_UTIL
#include <stdio.h>
#include "unittest.h"

int test_shuffle(void);
int test_shuffle_twod(void);
int test_fill_diagonals(void);
int test_backtrack(void);
int test_max_solutions(void);

int main()
{
  srand ( time(NULL) );
  int failed = 0;
  failed += test_shuffle();
  failed += test_shuffle_twod();
  failed += test_fill_diagonals();
  failed += test_backtrack();
  failed += test_max_solutions();

  if (failed) {
    printf("FAIL %d test cases\n", failed);
    return failed;
  } else {
    printf("PASS all test cases\n");
    return 0;
  }
}

int test_shuffle(void)
{
  START_TEST_CASE("shuffle array");
  int row_og[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int row[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  shuffle_arr(row, 9);
  for (int i = 0; i < 9; i++) {
    printf("%d ", row[i]);
  }
  printf("\n");
  EXPECT(row[0] != row_og[0] || row[1] != row_og[1] || row[2] != row_og[2]);
  END_TEST_CASE;
  return TEST_RESULT;
}

int test_shuffle_twod(void)
{
  START_TEST_CASE("shuffle twod array");
  int array_og[9][2];
  int array[9][2];
  int num = 0;
  for (int i = 0; i < 9; i++) {
    array[i][0] = num;
    array_og[i][0] = num;

    array[i][1] = num;
    array_og[i][1] = num;
    num++;
  }
  shuffle_arr_twod(array, 9);
  for (int i = 0; i < 9; i++) {
    printf("[%d, %d] ", array[i][0], array[i][1]);
  }
  printf("\n");
  EXPECT(array[0][0] != array_og[0][0] || array[1][0] != array_og[1][0] || array[2][0] != array_og[2][0]);
  END_TEST_CASE;
  return TEST_RESULT;
}

int test_fill_diagonals(void)
{
  START_TEST_CASE("fill diagonals");
  board board;
  for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0;
        }
  }
  fill_diagonals(board);
  // board_print(board);
  EXPECT(is_valid(board));
  END_TEST_CASE;
  return TEST_RESULT;
}

int test_backtrack(void)
{
  START_TEST_CASE("backtrack");
  board board;
  // for (int i = 0; i < 9; i++) {
  //   for (int j = 0; j < 9; j++) {
  //       board[i][j] = 0;
  //   }
  // }
  // fill_diagonals(board);
  
  // basic test with solvable board
  FILE *fp = fopen("solvable.txt", "r");
  board_scan(board, fp);
  fclose(fp);
  editable_spots_t spots = board_editable_spots(board);
  int num_solutions = 0;
  bool solved = backtrack(board, spots, 1, 0, &num_solutions);
  board_print(board);
  printf("\n");

  EXPECT(solved);
  EXPECT(num_solutions == 1);
  editable_spots_delete(spots);

  // see if it can solve a puzzle with multiple solutions
  fp = fopen("mult_sols.txt", "r");
  board_scan(board, fp);
  fclose(fp);
  spots = board_editable_spots(board);
  num_solutions = 0;
  solved = backtrack(board, spots, 1, 0, &num_solutions);
  board_print(board);
  printf("\n");

  EXPECT(solved);
  EXPECT(num_solutions == 1);
  editable_spots_delete(spots);

  // return num_solutions 0 for no solutions 
  fp = fopen("not_solvable.txt", "r");
  board_scan(board, fp);
  fclose(fp);
  spots = board_editable_spots(board);
  num_solutions = 0;
  solved = backtrack(board, spots, 1, 0, &num_solutions);
  board_print(board);
  printf("\n");

  EXPECT(!solved);
  EXPECT(num_solutions == 0);
  editable_spots_delete(spots);

  END_TEST_CASE;
  return TEST_RESULT;
}

int test_max_solutions(void)
{
  START_TEST_CASE("max solutions");
  board board;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
        board[i][j] = 0;
    }
  }
  fill_diagonals(board);
  editable_spots_t spots = board_editable_spots(board);
  int num_solutions = 0;
  bool solved = backtrack(board, spots, 2, 0, &num_solutions);
  EXPECT(num_solutions == 2);
  EXPECT(solved);
  END_TEST_CASE;
  return TEST_RESULT;
}

#endif // UNIT_TEST_UTIL


