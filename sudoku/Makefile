# Makefile for 'sudoku.c', 'solve.c', and 'create.c'
#
# kumquat
# CS50, Summer 2021

PROG_SOLVE = solve 
OBJS_SOLVE = solve.o

PROG_CREATE = create
OBJS_CREATE = create.o

PROG_DRIVER = sudoku
OBJS_DRIVER = sudoku.o

LLIBS = ../common/common.a

# uncomment the following to turn on verbose memory logging
TESTING= #-DDEBUG

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) 
CC = gcc
MAKE = make

all: solve create driver

$(PROG_SOLVE): $(OBJS_SOLVE) $(LLIBS)
		$(CC) $(CFLAGS) $^ -o $@

$(PROG_CREATE): $(OBJS_CREATE) $(LLIBS)
		$(CC) $(CFLAGS) $^ -o $@

$(PROG_DRIVER): $(OBJS_DRIVER) $(LLIBS)
		$(CC) $(CFLAGS) $^ -o $@

solve.o: ../common/board.h ../common/utilities.h

create.o: ../common/board.h ../common/utilities.h

sudoku.o: solve.h create.h 


.PHONY: all test clean

unit_solve: solve.o $(LLIBS)
	$(CC) $(CFLAGS) -DUNITTEST $^ -o unit_solve

unit_create: create.o $(LLIBS)
	$(CC) $(CFLAGS) -DUNITTEST $^ -o unit_create


clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG_SOLVE)
	rm -f $(PROG_CREATE)
	rm -f $(PROG_DRIVER)

