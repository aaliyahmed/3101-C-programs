#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int serverSocketID = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9001);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    int connectStatus = connect(serverSocketID, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    if (connectStatus == -1)
    {
        printf("Error: Could not connect to the server.\n");
    }
    else
    {
        char fileName[255];
        char serverMsg[255];

        printf("Enter file name: ");
        fgets(fileName, sizeof(fileName), stdin);

        send(serverSocketID, fileName, sizeof(fileName), 0);

        recv(serverSocketID, serverMsg, sizeof(serverMsg), 0);

        printf("Message from the Server:\n%s\n", serverMsg);
    }

    close(serverSocketID);

    return 0;
}