Problem Statement:
This program is about building a simple client and server using C. The client sends a filename to the server, and the server sends back the contents of that file. The file has to be text and less than 255 characters. The program should also handle errors like if the file doesn’t exist or the name is wrong.

Describe the Solution:
I made two programs called server.c and client.c. The server waits for a client to connect and send a filename. When it gets the filename, it checks if the file exists and reads it. If everything is good, it sends the file contents back. If not, it sends an error message. The client connects to the server, asks the user for a filename, sends it, and then prints whatever the server sends back.

Pros:
- Simple and easy to understand
- Server can take multiple requests using a loop
- Has basic error handling for files
- Uses sockets to show networking concepts

Cons:
- Only handles one client at a time
- Limited to files under 255 characters
- No security or advanced features
