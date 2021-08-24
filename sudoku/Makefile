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

PROG_FUZZ = fuzztest
OBJS_FUZZ = fuzztest.o solve.o create.o

LLIBS = ../common/common.a

FLAGS = #-DDEBUG

CREATE_UNIT=unit_create
SOLVE_UNIT=unit_solve

$(CREATE_UNIT): FLAGS += -DUNIT_TEST_CREATE
$(SOLVE_UNIT): FLAGS += -DUNIT_TEST_SOLVE
$(PROG_FUZZ): FLAGS += -DUNIT_TEST_FUZZ

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) 
CC = gcc
MAKE = make

driver: sudoku.o solve.o create.o ../common/common.a
	$(CC) $(CFLAGS) $^ -o sudoku

solve.o: ../common/board.h ../common/utilities.h .FORCE

create.o: ../common/board.h ../common/utilities.h .FORCE

sudoku.o: solve.h create.h ../common/board.h .FORCE

fuzztest.o: solve.o create.o ../common/board.h ../common/unittest.h ../common/utilities.h .FORCE


.PHONY: all test clean .FORCE

.FORCE: 

unit: unit_solve unit_create

unit_solve: solve.o $(LLIBS) 
	$(CC) $(CFLAGS) $^ -o unit_solve

unit_create: create.o $(LLIBS)
	$(CC) $(CFLAGS) $^ -o unit_create

$(PROG_FUZZ): $(OBJS_FUZZ) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@


clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG_SOLVE)
	rm -f $(PROG_CREATE)
	rm -f $(PROG_DRIVER)
	rm -f $(PROG_FUZZ)
