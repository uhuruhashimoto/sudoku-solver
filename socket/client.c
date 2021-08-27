/*
* EC Client for socket transmission of sudoku
* Client creates a sudoku, serializes it, and passes it to server to solve
*
* Uhuru Hashimoto
* Kumquat CS50 21X
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //for closing files
#include <arpa/inet.h>   //inet_addr
#include <sys/socket.h> //for sock
#include <netinet/in.h> //for servaddr
#include <json-c/json.h> //for serialization
#include "../common/board.h" //board functionality
#include "../common/utilities.h"
#include "../sudoku/solve.h"
#include "../sudoku/create.h"


int main() {
    const int PORT = 3001;
    board puzzle; //stores created sudoku
    board buf; //stores solution
    int status = 0;
    int sockfd;
    struct sockaddr_in servaddr;

    board_initialize(puzzle);
    board_initialize(buf);

    //create socket
    fprintf(stdout, "Creating socket...\n");
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed to create socket");
        return ++status;
    }
    servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

    //connecting to socket
    fprintf(stdout, "Connecting to socket at port %d...\n", PORT);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("Failed to connect to socket");
        return ++status;
	}
    fprintf(stdout, "Connected.\n");

    //create sudoku
    fprintf(stdout, "Created sudoku:\n");
    create(puzzle);

    //send sudoku
    fprintf(stdout, "Sending sudoku...\n");
    if ((send(sockfd, puzzle, 81*4, 0)) < 0) {
        perror("Failed to send sudoku");
        close(sockfd);
        return ++status;
    }

    //receive answer
    if ((recv(sockfd, &buf, 81*4, 0)) < 0) {
        perror("Failed to recieve solution");
        close(sockfd);
        return ++status;
    }
    fprintf(stdout, "Recieved solution:\n");
    board_print(buf);

    //close socket
    fprintf(stdout, "Exiting...\n");
    close(sockfd);
}
