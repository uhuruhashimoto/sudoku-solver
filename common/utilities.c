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

/** Unit tests **/

#ifdef UNIT_TEST_UTIL
#include <stdio.h>
#include "unittest.h"

int test_shuffle(void);
int test_fill_diagonals(void);

int main()
{
  srand ( time(NULL) );
  int failed = 0;
  failed += test_shuffle();
  failed += test_fill_diagonals();

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
  board_print(board);
  END_TEST_CASE;
  return TEST_RESULT;
}

#endif // UNIT_TEST