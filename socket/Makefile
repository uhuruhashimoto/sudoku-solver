# Makefile for client and server
# run `make client` to make client executable
# run `make server` to make server executable
# assumes user has already built the library
# 
# Kumquat CS50 21X

OBJ_CLIENT = client.o 
OBJ_SERVER = server.o 
CC = gcc
FLAGS = -DSOCKET
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)

all: client server 

client: $(OBJ_CLIENT) ../sudoku/create.o ../common/common.a
	$(CC) $(CFLAGS) $^ -o client

server: $(OBJ_SERVER) ../sudoku/solve.o ../common/common.a
	$(CC) $(CFLAGS) $^ -o server

client.o: ../common/board.h ../common/utilities.h ../sudoku/create.h 
server.o: ../common/board.h ../common/utilities.h ../sudoku/solve.h 
../sudoku/create.o: ../sudoku/create.h 
../sudoku/solve.o: ../sudoku/solve.h 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f client
	rm -f server