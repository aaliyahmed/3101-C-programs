#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // create client socket
    int serverSocketID = socket(AF_INET, SOCK_STREAM, 0);

    // define server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9001);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // connect to server
    int connectStatus = connect(serverSocketID, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    if (connectStatus == -1) {
        printf("Error: Could not connect to server\n");
    } else {
        char eventInfo[255];
        char serverMsg[255];

        printf("Enter event to send to server: ");
        fgets(eventInfo, sizeof(eventInfo), stdin);

        // send event to server
        send(serverSocketID, eventInfo, sizeof(eventInfo), 0);

        // receive response from server
        recv(serverSocketID, serverMsg, sizeof(serverMsg), 0);

        printf("Message from server: %s\n", serverMsg);
    }

    close(serverSocketID);

    return 0;
}