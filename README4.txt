Problem Statement:
This program is a seat reservation system for Colossus Airlines. The plane has 48 seats and there are two flights, outbound and inbound. The program lets the user choose a flight and manage reservations. For this version, the seat data is stored in a file so it is not lost when the program ends.

Describe the Solution:
I used an array of structures for each flight. Each seat stores the seat number, whether it is taken, and the passenger’s first and last name. I added file input and output so the program can save the reservation data to files and load it back in when the program starts again.

Pros:
- Saves data even after the program closes
- Keeps the two flights separate
- Uses functions and menus to keep the code organized

Cons:
- Works for only 48 seats
- Sorting is basic
- Input checking could be better