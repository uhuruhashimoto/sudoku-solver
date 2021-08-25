/*
* EC Server for socket transmission of sudoku
* Server recieves a sudoku, solves it, and sends the solved sudoku back to client
*
* Uhuru Hashimoto
* Kumquat CS50 21X
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for sock
#include <netinet/in.h> //for servaddr
#include <json-c/json.h> //for serialization
#include "../common/board.h" //board functionality
#include "../common/utilities.h"


int main() {
    const int PORT = 60065;
    int status = 0;
    int sockfd;
    struct sockaddr_in servaddr;

    //create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "Error: failed to create socket\n");
        return ++status;
    }
    servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		fprintf(stderr, "Error: failed to connect to socket\n");
        return ++status;
	}

    //recieve sudoku

    //solve sudoku

    //serialize

    //send solution

    //close socket
    fprintf(stdout, "Exiting...\n");
    close(sockfd);
}