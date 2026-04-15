#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SEATS 48
#define SIZE 20

struct seat
{
    int seatnum;
    int taken;
    char last[SIZE];
    char first[SIZE];
};

void setSeats(struct seat flight[], int n);
void showMainMenu(void);
void showFlightMenu(void);
void handleFlight(struct seat flight[], char name[], char filename[]);
void emptyCount(struct seat flight[], int n);
void emptyList(struct seat flight[], int n);
void alphaList(struct seat flight[], int n);
void assignSeat(struct seat flight[], int n, char filename[]);
void deleteSeat(struct seat flight[], int n, char filename[]);
void loadSeats(struct seat flight[], int n, char filename[]);
void saveSeats(struct seat flight[], int n, char filename[]);

int main(void)
{
    struct seat outbound[SEATS];
    struct seat inbound[SEATS];
    char choice;

    setSeats(outbound, SEATS);
    setSeats(inbound, SEATS);

    loadSeats(outbound, SEATS, "outbound.dat");
    loadSeats(inbound, SEATS, "inbound.dat");

    showMainMenu();
    scanf(" %c", &choice);
    choice = tolower(choice);

    while (choice != 'c')
    {
        if (choice == 'a')
            handleFlight(outbound, "Outbound Flight", "outbound.dat");
        else if (choice == 'b')
            handleFlight(inbound, "Inbound Flight", "inbound.dat");
        else
            printf("Invalid choice.\n");

        showMainMenu();
        scanf(" %c", &choice);
        choice = tolower(choice);
    }

    saveSeats(outbound, SEATS, "outbound.dat");
    saveSeats(inbound, SEATS, "inbound.dat");

    printf("Have a good one!\n");

    return 0;
}

void setSeats(struct seat flight[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        flight[i].seatnum = i + 1;
        flight[i].taken = 0;
        strcpy(flight[i].first, "");
        strcpy(flight[i].last, "");
    }
}

void loadSeats(struct seat flight[], int n, char filename[])
{
    FILE *fp;

    fp = fopen(filename, "rb");

    if (fp == NULL)
        return;

    fread(flight, sizeof(struct seat), n, fp);
    fclose(fp);
}

void saveSeats(struct seat flight[], int n, char filename[])
{
    FILE *fp;

    fp = fopen(filename, "wb");

    if (fp == NULL)
    {
        printf("Could not save %s\n", filename);
        return;
    }

    fwrite(flight, sizeof(struct seat), n, fp);
    fclose(fp);
}

void showMainMenu(void)
{
    printf("\nTo choose a function, enter its letter label:\n");
    printf("a. Outbound Flight\n");
    printf("b. Inbound Flight\n");
    printf("c. Quit\n");
    printf("Choice: ");
}

void showFlightMenu(void)
{
    printf("\na. Show number of empty seats\n");
    printf("b. Show list of empty seats\n");
    printf("c. Show alphabetical list of seats\n");
    printf("d. Assign a customer to a seat assignment\n");
    printf("e. Delete a seat assignment\n");
    printf("f. Return to main menu\n");
    printf("Choice: ");
}

void handleFlight(struct seat flight[], char name[], char filename[])
{
    char choice;

    printf("\n%s\n", name);
    showFlightMenu();
    scanf(" %c", &choice);
    choice = tolower(choice);

    while (choice != 'f')
    {
        switch (choice)
        {
            case 'a':
                emptyCount(flight, SEATS);
                break;
            case 'b':
                emptyList(flight, SEATS);
                break;
            case 'c':
                alphaList(flight, SEATS);
                break;
            case 'd':
                assignSeat(flight, SEATS, filename);
                break;
            case 'e':
                deleteSeat(flight, SEATS, filename);
                break;
            default:
                printf("Invalid choice.\n");
        }

        printf("\n%s\n", name);
        showFlightMenu();
        scanf(" %c", &choice);
        choice = tolower(choice);
    }
}

void emptyCount(struct seat flight[], int n)
{
    int i;
    int count = 0;

    for (i = 0; i < n; i++)
    {
        if (flight[i].taken == 0)
            count++;
    }

    printf("Empty seats: %d\n", count);
}

void emptyList(struct seat flight[], int n)
{
    int i;

    printf("Open seats: ");
    for (i = 0; i < n; i++)
    {
        if (flight[i].taken == 0)
            printf("%d ", flight[i].seatnum);
    }
    printf("\n");
}

void alphaList(struct seat flight[], int n)
{
    struct seat temp[SEATS];
    struct seat hold;
    int i, j, count = 0;

    for (i = 0; i < n; i++)
    {
        if (flight[i].taken == 1)
        {
            temp[count] = flight[i];
            count++;
        }
    }

    if (count == 0)
    {
        printf("No assigned seats.\n");
        return;
    }

    for (i = 0; i < count - 1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (strcmp(temp[i].last, temp[j].last) > 0)
            {
                hold = temp[i];
                temp[i] = temp[j];
                temp[j] = hold;
            }
        }
    }

    printf("Assigned seats in alphabetical order:\n");
    for (i = 0; i < count; i++)
    {
        printf("Seat %d - %s, %s\n", temp[i].seatnum, temp[i].last, temp[i].first);
    }
}

void assignSeat(struct seat flight[], int n, char filename[])
{
    int num;

    printf("Enter seat number (1-48) or 0 to cancel: ");
    scanf("%d", &num);

    if (num == 0)
    {
        printf("Canceled.\n");
        return;
    }

    if (num < 1 || num > n)
    {
        printf("Invalid seat number.\n");
        return;
    }

    if (flight[num - 1].taken == 1)
    {
        printf("Seat already assigned.\n");
        return;
    }

    printf("Enter first name (q to cancel): ");
    scanf("%19s", flight[num - 1].first);

    if (strcmp(flight[num - 1].first, "q") == 0 || strcmp(flight[num - 1].first, "Q") == 0)
    {
        strcpy(flight[num - 1].first, "");
        printf("Canceled.\n");
        return;
    }

    printf("Enter last name (q to cancel): ");
    scanf("%19s", flight[num - 1].last);

    if (strcmp(flight[num - 1].last, "q") == 0 || strcmp(flight[num - 1].last, "Q") == 0)
    {
        strcpy(flight[num - 1].first, "");
        strcpy(flight[num - 1].last, "");
        printf("Canceled.\n");
        return;
    }

    flight[num - 1].taken = 1;
    saveSeats(flight, n, filename);
    printf("Seat %d assigned.\n", num);
}

void deleteSeat(struct seat flight[], int n, char filename[])
{
    int num;

    printf("Enter seat number to delete or 0 to cancel: ");
    scanf("%d", &num);

    if (num == 0)
    {
        printf("Canceled.\n");
        return;
    }

    if (num < 1 || num > n)
    {
        printf("Invalid seat number.\n");
        return;
    }

    if (flight[num - 1].taken == 0)
    {
        printf("Seat is already empty.\n");
        return;
    }

    flight[num - 1].taken = 0;
    strcpy(flight[num - 1].first, "");
    strcpy(flight[num - 1].last, "");

    saveSeats(flight, n, filename);
    printf("Seat %d deleted.\n", num);
}