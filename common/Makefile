# Makefile for common library
#   Builds and compiles all common functions into a library.
#
# CS50, Summer 2021

# object files, and the target library
OBJS = board.o utilities.o file.o
LIB = common.a

FLAGS = #-DUNITTEST # -DMEMTEST  # -DDEBUG 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# unit test target for board
unit_board: board.o 
	$(CC) $(CFLAGS) -DUNITTEST $^ -o unit_board

unit_utilities: utilities.o 
	$(CC) $(CFLAGS) -DUNITTEST $^ -o unit_utilities

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
