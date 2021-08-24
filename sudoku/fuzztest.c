/* 
 * fuzztest.c - CS50 'fuzztest' module
 *
 * see DESIGN.md and IMPLEMENTATION.md for more information.
 *
 * CS50
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../common/unittest.h"
#include "../common/board.h"
#include "create.h"
#include "solve.h"
#include "../common/utilities.h"

int main() {
	srand ( time(NULL) );
	START_TEST_CASE("create and solve boards");

	// create and solve 10 boards
	for (int i = 1; i <= 10; i++) {
		board puzzle;
		board_initialize(puzzle);
		create(puzzle);

		// newly created boards are valid but not complete
		EXPECT(is_valid(puzzle));
		EXPECT(!is_complete(puzzle));
		if (is_valid(puzzle) && !is_complete(puzzle)) {
			printf("Board %d was created successfully\n", i);
		}

		// check unique solution
		int num_solutions = 0;
		board copy; 
		copy_board(puzzle, copy);
		editable_spots_t spots = board_editable_spots(puzzle);
		backtrack(copy, spots, 2, 0, &num_solutions);
		editable_spots_delete(spots);
		EXPECT(num_solutions == 1);
		printf("Board %d has %d solutions\n", i, num_solutions);

		// check solved puzzle
		solve(puzzle);
		EXPECT(is_valid(puzzle));
		EXPECT(is_complete(puzzle));
		if (is_valid(puzzle) && is_complete(puzzle)) {
			printf("Board %d was solved successfully\n", i);
		}
	}

  END_TEST_CASE;
  return TEST_RESULT;
}