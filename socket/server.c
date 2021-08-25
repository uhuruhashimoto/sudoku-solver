/*
* EC Server for socket transmission of sudoku
* Server recieves a sudoku, solves it, and sends the solved sudoku back to client
*
* Uhuru Hashimoto
* Kumquat CS50 21X
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //for closing files
#include <sys/socket.h> //for sock
#include <netinet/in.h> //for servaddr
#include <json-c/json.h> //for serialization
#include "../common/board.h" //board functionality
#include "../common/utilities.h"
#include "../sudoku/solve.h"
#include "../sudoku/create.h"


int main() {
    const int PORT = 60065;
    int status = 0;
    int sockfd;
    struct sockaddr_in servaddr;
    board buf;

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
    if ((recv(sockfd, &buf, 81, 0)) < 0) {
        fprintf(stderr, "Error: failed to recieve solution\n");
        close(sockfd);
        return ++status;
    }
    fprintf(stdout, "Recieved sudoku!\n");
    board_print(buf);

    //solve sudoku
    fprintf(stdout, "Solving sudoku...\n");
    solve(buf);

    //send solution
    fprintf(stdout, "Sending solution...\n");
    if ((send(sockfd, buf, 81, 0)) < 0) {
        fprintf(stderr, "Error: failed to send sudoku\n");
        close(sockfd);
        return ++status;
    }
    fprintf(stdout, "Solution sent.\n");

    //close socket
    fprintf(stdout, "Exiting...\n");
    close(sockfd);
}