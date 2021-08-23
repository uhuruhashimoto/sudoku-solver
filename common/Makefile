# Makefile for common library
#   Builds and compiles all common functions into a library.
#
# CS50, Summer 2021

# object files, and the target library
OBJS = board.o utilities.o file.o
LIB = common.a

FLAGS = # -DUNIT_TEST # -DUNIT_TEST_UTIL # -DMEMTEST  # -DDEBUG 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc 

BOARD_UNIT=unit_board
UTIL_UNIT=unit_utilities
UTIL_UNIT_EXTRA=unit_utilities_re

$(BOARD_UNIT): FLAGS += -DUNIT_TEST_BOARD
$(UTIL_UNIT): FLAGS += -DUNIT_TEST_UTIL
$(UTIL_UNIT_EXTRA): FLAGS += -DUNIT_TEST_UTIL

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# unit test target for board
unit_board: board.o unittest.h file.o
	$(CC) $(CFLAGS) $^ -o unit_board

unit_utilities: board.o utilities.o unittest.h file.o
	$(CC) $(CFLAGS) $^ -o unit_utilities

unit_utilities_re: board.o utilities.o unittest.h file.o
	make board.o
	$(CC) $(CFLAGS) $^ -o unit_utilities


# Dependencies: object files depend on header files
board.o: board.h .FORCE
utilities.o: utilities.h .FORCE
file.o: file.h 

# helper target for unit test
.FORCE: 

.PHONY: clean .FORCE

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
	rm -f unit_*

unit: unit_board unit_utilities_re

