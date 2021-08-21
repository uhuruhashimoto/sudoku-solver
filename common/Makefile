# Makefile for common library
#   Builds and compiles all common functions into a library.
#
# CS50, Summer 2021

# object files, and the target library
OBJS = board.o utilities.o file.o
LIB = common.a

FLAGS = -DUNIT_TEST -DUNIT_TEST_UTIL # -DMEMTEST  # -DDEBUG 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc

BOARD_UNIT=unit_board
UTIL_UNIT=unit_utilities

$(BOARD_UNIT): EXTRA_FLAGS := -DUNIT_TEST_BOARD
$(UTIL_UNIT): EXTRA_FLAGS := -DUNIT_TEST_UTIL

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# unit test target for board
unit_board: board.o unittest.h file.o
	$(CC) $(CFLAGS) $(EXTRA_FLAGS) $^ -o unit_board

unit_utilities: utilities.o unittest.h board.o file.o
	$(CC) $(CFLAGS) $(EXTRA_FLAGS) $^ -o unit_utilities


# Dependencies: object files depend on header files
board.o: board.h 
utilities.o: utilities.h 
file.o: file.h

.PHONY: clean

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
	rm -f unit_*

unit:	unit_utilities unit_board