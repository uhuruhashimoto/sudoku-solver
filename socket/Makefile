# Makefile for client and server
# run `make client` to make client executable
# run `make server` to make server executable
# assumes user has already built the library
# 
# Kumquat CS50 21X

OBJ_CLIENT = client.o 
OBJ_SERVER = server.o 
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

all: client server solve.o create.o ../common/common.a

client: $(OBJ_CLIENT) create.o ../common/common.a
	$(CC) $(CFLAGS) $^ -o client

server: $(OBJ_SERVER) solve.o ../common/common.a
	$(CC) $(CFLAGS) $^ -o server

client.o: ../common/board.h ../common/utilities.h ../sudoku/create.h client.c
server.o: ../common/board.h ../common/utilities.h ../sudoku/solve.h 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f client
	rm -f server