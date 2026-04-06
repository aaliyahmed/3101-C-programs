Problem Statement:
This program is a seat reservation system for Colossus Airlines. The plane has 48 seats and there are two flights (outbound and inbound). The user can choose a flight and manage seat assignments.

Describe the Solution:
I used an array of structures to store each seat. Each seat keeps track of the seat number, if it is taken, and the passenger’s first and last name. There are two arrays, one for each flight. The program uses menus and functions to let the user view empty seats, assign seats, delete seats, and show assigned seats in alphabetical order.

Pros:
- Easy to use with menus
- Keeps flights separate
- Covers all required features

Cons:
- Only works for 48 seats
- Sorting is basic (last name only)
- Input checking could be better