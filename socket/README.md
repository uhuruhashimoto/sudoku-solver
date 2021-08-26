# Socket README
# Kumquat CS50 21X

# Overview
This directory contains a client and server program. 
- The server opens a TCP socket and waits for an incoming connection. When it recieves one, it scans a sudoku into a buffer, solves it, sends the solved sudoku to the client, and exits. 
- The client opens a TCP socket on the same port as the server. It then creates a sudoku, and sends the created puzzle to the server. When it recieves a reply, it prints the solution, then exits. 


# Build
To build server, run `make server`. To build client, run `make client`. To build both, run `make all`. Please note that these require a built `../common/common.a` library, which may be created by running `make` from common or any top level directory. 

# Run
To run the program, first run the server (which will create a socket and listen for an incoming connection). To do this, simply run `./server`. To run the client, run `./client` from another terminal. 

*Note: Currently the port is set to a default of 3001, which may be changed by altering the constant int PORT in both the server.c and client.c programs (which is currently located in the driver). If the port is in use, this may be necessary to run the program.*