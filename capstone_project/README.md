Calendar Management System

Problem Statement:
This program is a calendar management system written in C. The user can add, view, update, delete, and search for events. The program also saves events to a file so the data is not lost after closing the program. A client and server were also added so events can be sent using sockets.

Design and Architecture Details:
The program uses structs and arrays to store event information. Each event stores an ID, title, date, time, location, and description.
The program is separated into multiple files:
- main.c handles the menu
- calendar_functions.c handles the event functions
- calendar.h contains the struct and function declarations
- server.c handles the server socket
- client.c handles the client socket
File I/O is used to save and load events from calendar_data.txt.
The networking part uses TCP sockets. The client sends an event message to the server and the server receives it and sends a response back.

Pros:
- Simple and easy to use
- Saves event data using files
- Uses CRUD operations
- Includes socket programming
- Organized into multiple files

Cons:
- Limited to 100 events
- Input validation could be better
- Server only handles simple text messages
- No graphical interface
