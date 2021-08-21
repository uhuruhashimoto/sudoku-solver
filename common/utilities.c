/* 
 * utilities.c - CS50 'utilities' module
 *
 * see utilities.h for more information.
 *
 * CS50
 * Tyler Vergho
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include "board.h"

static inline void shuffle_arr(int arr[], int n)
{
  int i, j, temp;
  for (i = n - 1; i > 0; i--) {
    j = rand() % (i + 1);
    temp = arr[j];
    arr[j] = arr[i];
    arr[i] = temp;
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
int test_fill_diagonals(void);
int test_backtrack(void);

int main()
{
  srand ( time(NULL) );
  int failed = 0;
  failed += test_shuffle();
  failed += test_fill_diagonals();
  failed += test_backtrack();

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
  EXPECT(row[0] != row_og[0] || row[1] != row_og[1]);
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
  FILE *fp = fopen("./test_board_2.txt", "r");
  board_scan(board, fp);
  fclose(fp);
  editable_spots_t spots = board_editable_spots(board);
  int num_solutions = 0;
  bool solved = backtrack(board, spots, 1, 0, &num_solutions);
  EXPECT(solved);
  board_print(board);
  END_TEST_CASE;
  return TEST_RESULT;
}

#endif // UNIT_TEST