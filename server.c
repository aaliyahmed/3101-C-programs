#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int serverSocketID;

void handle_signal(int sig)
{
    printf("\nServer shutting down...\n");
    close(serverSocketID);
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, handle_signal);

    serverSocketID = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9001);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocketID, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    printf("Listening for Connections\n");

    listen(serverSocketID, 1);

    while (1)
    {
        printf("Waiting for next request from Client\n");

        int clientSocket = accept(serverSocketID, NULL, NULL);

        char fileName[255];
        char serverMsg[255];
        FILE *fp;
        long fileSize;

        memset(fileName, 0, sizeof(fileName));
        memset(serverMsg, 0, sizeof(serverMsg));

        recv(clientSocket, fileName, sizeof(fileName), 0);

        fileName[strcspn(fileName, "\n")] = '\0';

        if (strlen(fileName) == 0)
        {
            strcpy(serverMsg, "Error: Invalid file name.");
        }
        else
        {
            fp = fopen(fileName, "r");

            if (fp == NULL)
            {
                strcpy(serverMsg, "Error: File not found.");
            }
            else
            {
                fseek(fp, 0, SEEK_END);
                fileSize = ftell(fp);
                rewind(fp);

                if (fileSize > 255)
                {
                    strcpy(serverMsg, "Error: File size exceeds 255 characters.");
                }
                else
                {
                    fread(serverMsg, sizeof(char), fileSize, fp);
                    serverMsg[fileSize] = '\0';
                }

                fclose(fp);
            }
        }

        send(clientSocket, serverMsg, sizeof(serverMsg), 0);

        printf("Responded to client request\n");

        close(clientSocket);
    }

    return 0;
}