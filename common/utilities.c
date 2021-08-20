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

typedef int board[9][9];

static inline void shuffle_arr(int (*arr)[], int n)
{
  int i, j, tmp;
  for (i = n - 1; i > 0; i--) {
    j = rand() % (i + 1);
    tmp = (*arr)[j];
    (*arr)[j] = (*arr)[i];
    (*arr)[i] = tmp;
  }
}

/** Unit tests **/

#ifdef UNIT_TEST
#include <stdio.h>
#include "unittest.h"

int test_shuffle(void);

int main()
{
  int failed = 0;
  failed += test_shuffle();

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
  shuffle_arr(&row, 9);
  EXPECT(row[0] != row_og[0] || row[1] != row_og[1]);
  END_TEST_CASE;
  return TEST_RESULT;
}

#endif // UNIT_TEST