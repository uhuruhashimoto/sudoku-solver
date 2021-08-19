# Makefile for Sudoku, CS50 Group Project
#
# CS 50, Summer 2021

.PHONY: all valgrind clean

############## default: make all libs and programs ##########
all: 
	make -C common
	make -C sudoku

############## valgrind all programs ##########
valgrind: all
	make -C common valgrind
	make -C sudoku valgrind

############## clean  ##########
clean:
	rm -f *~
	make -C common clean
	make -C sudoku clean

