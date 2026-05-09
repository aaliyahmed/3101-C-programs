#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"

int main() {
    int choice;

    // load saved events when program starts
    load_events();

    while (1) {
        printf("\nCalendar Management System\n");
        printf("1. Add Event\n");
        printf("2. View Events\n");
        printf("3. Update Event\n");
        printf("4. Delete Event\n");
        printf("5. Search Events\n");
        printf("0. Exit\n");
        printf("Choice: ");

        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                add_event();
                break;
            case 2:
                view_events();
                break;
            case 3:
                update_event();
                break;
            case 4:
                delete_event();
                break;
            case 5:
                search_events();
                break;
            case 0:
                printf("Goodbye\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}