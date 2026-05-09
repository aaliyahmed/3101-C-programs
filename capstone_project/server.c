#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // create server socket
    int serverSocketID = socket(AF_INET, SOCK_STREAM, 0);

    // message from server to client
    char serverMsg[255] = "Server received the calendar event";

    // define server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9001);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // bind socket
    bind(serverSocketID, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    printf("Calendar server is listening\n");

    // listen for connections
    listen(serverSocketID, 1);

    while (1) {
        printf("Waiting for event from client\n");

        // accept client connection
        int clientSocket = accept(serverSocketID, NULL, NULL);

        char clientMsg[255];
        memset(clientMsg, 0, sizeof(clientMsg));

        // receive message from client
        recv(clientSocket, clientMsg, sizeof(clientMsg), 0);

        printf("Event received from client: %s\n", clientMsg);

        // send response to client
        send(clientSocket, serverMsg, sizeof(serverMsg), 0);

        close(clientSocket);
    }

    return 0;
}