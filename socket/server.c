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
    const int PORT = 3000;
    int status = 0;
    int sockfd;
    int clientfd;
    struct sockaddr_in servaddr;
    board buf;
    socklen_t size;

    //initialize board
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

    //bind
    fprintf(stdout, "Binding socket...\n");
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Failed to bind to socket");
        return ++status;
	}

    //listen
    if(listen(sockfd, SOMAXCONN) < 0){
        printf("Error listening for connections\n");
        exit(0);
    }
    fprintf(stdout, "Listening for clients at port %d...\n", PORT);

    size = sizeof(servaddr);
    if ((clientfd = accept(sockfd, (struct sockaddr *)&servaddr, &size)) < 0) {
        perror("Rejected client");
        close(sockfd);
        return ++status;
    }
    fprintf(stdout, "Accepted client.\n");

    //recieve sudoku
    if ((recv(clientfd, &buf, 81*4, 0)) < 0) {
        perror("Failed to recieve sudoku");
        close(sockfd);
        return ++status;
    }
    fprintf(stdout, "Recieved sudoku!\n");
    board_print(buf);

    //solve sudoku
    fprintf(stdout, "Solving sudoku...\n");
    solve(buf);
    fprintf(stdout, "Solution:\n");
    board_print(buf);

    //send solution
    fprintf(stdout, "Sending solution...\n");
    if ((send(sockfd, buf, 81, 0)) < 0) {
        perror("Failed to send solution");
        close(sockfd);
        return ++status;
    }
    fprintf(stdout, "Solution sent.\n");

    //close socket
    fprintf(stdout, "Exiting...\n");
    close(sockfd);
}
