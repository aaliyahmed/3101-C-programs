#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calendar.h"

Event events[MAX_EVENTS];
int event_count = 0;
int next_id = 1;

// save all events to file
void save_events() {
    FILE *file = fopen(DATA_FILE, "w");

    if (!file) {
        return;
    }

    fprintf(file, "%d\n%d\n", event_count, next_id);

    for (int i = 0; i < event_count; i++) {
        fprintf(file, "%d;%s;%s;%s;%s;%s\n",
                events[i].id,
                events[i].title,
                events[i].date,
                events[i].time,
                events[i].location,
                events[i].description);
    }

    fclose(file);
}

// load events from file
void load_events() {
    FILE *file = fopen(DATA_FILE, "r");

    if (!file) {
        return;
    }

    fscanf(file, "%d\n%d\n", &event_count, &next_id);

    for (int i = 0; i < event_count; i++) {

        char line[MAX_STRING * 5];

        fgets(line, sizeof(line), file);

        char *token = strtok(line, ";");
        events[i].id = atoi(token);

        token = strtok(NULL, ";");
        strcpy(events[i].title, token);

        token = strtok(NULL, ";");
        strcpy(events[i].date, token);

        token = strtok(NULL, ";");
        strcpy(events[i].time, token);

        token = strtok(NULL, ";");
        strcpy(events[i].location, token);

        token = strtok(NULL, "\n");
        strcpy(events[i].description, token);
    }

    fclose(file);
}

// add new event
void add_event() {

    if (event_count >= MAX_EVENTS) {
        printf("Calendar is full\n");
        return;
    }

    Event *e = &events[event_count];

    e->id = next_id++;

    printf("Event Title: ");
    fgets(e->title, MAX_STRING, stdin);
    e->title[strcspn(e->title, "\n")] = 0;

    printf("Date: ");
    fgets(e->date, MAX_STRING, stdin);
    e->date[strcspn(e->date, "\n")] = 0;

    printf("Time: ");
    fgets(e->time, MAX_STRING, stdin);
    e->time[strcspn(e->time, "\n")] = 0;

    printf("Location: ");
    fgets(e->location, MAX_STRING, stdin);
    e->location[strcspn(e->location, "\n")] = 0;

    printf("Description: ");
    fgets(e->description, MAX_STRING, stdin);
    e->description[strcspn(e->description, "\n")] = 0;

    event_count++;

    save_events();

    printf("Event added successfully\n");
}

// view all events
void view_events() {

    if (event_count == 0) {
        printf("No events found\n");
        return;
    }

    for (int i = 0; i < event_count; i++) {

        printf("\nEvent %d\n", i + 1);

        printf("ID: %d\n", events[i].id);
        printf("Title: %s\n", events[i].title);
        printf("Date: %s\n", events[i].date);
        printf("Time: %s\n", events[i].time);
        printf("Location: %s\n", events[i].location);
        printf("Description: %s\n", events[i].description);
    }
}
// update an event
void update_event() {

    if (event_count == 0) {
        printf("No events to update\n");
        return;
    }

    int id;
    int index = -1;
    char temp[MAX_STRING];

    printf("Enter event ID: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < event_count; i++) {
        if (events[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Event not found\n");
        return;
    }

    printf("Current title: %s\n", events[index].title);
    printf("New title or press enter to keep: ");
    fgets(temp, MAX_STRING, stdin);
    if (strlen(temp) > 1) {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(events[index].title, temp);
    }

    printf("Current date: %s\n", events[index].date);
    printf("New date or press enter to keep: ");
    fgets(temp, MAX_STRING, stdin);
    if (strlen(temp) > 1) {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(events[index].date, temp);
    }

    printf("Current time: %s\n", events[index].time);
    printf("New time or press enter to keep: ");
    fgets(temp, MAX_STRING, stdin);
    if (strlen(temp) > 1) {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(events[index].time, temp);
    }

    printf("Current location: %s\n", events[index].location);
    printf("New location or press enter to keep: ");
    fgets(temp, MAX_STRING, stdin);
    if (strlen(temp) > 1) {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(events[index].location, temp);
    }

    printf("Current description: %s\n", events[index].description);
    printf("New description or press enter to keep: ");
    fgets(temp, MAX_STRING, stdin);
    if (strlen(temp) > 1) {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(events[index].description, temp);
    }

    save_events();

    printf("Event updated successfully\n");
}

// delete an event
void delete_event() {

    if (event_count == 0) {
        printf("No events to delete\n");
        return;
    }

    int id;
    int index = -1;

    printf("Enter event ID: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < event_count; i++) {
        if (events[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Event not found\n");
        return;
    }

    for (int i = index; i < event_count - 1; i++) {
        events[i] = events[i + 1];
    }

    event_count--;

    save_events();

    printf("Event deleted successfully\n");
}

// search for events
void search_events() {

    if (event_count == 0) {
        printf("No events to search\n");
        return;
    }

    char search_term[MAX_STRING];
    int found = 0;

    printf("Enter search term: ");
    fgets(search_term, MAX_STRING, stdin);
    search_term[strcspn(search_term, "\n")] = 0;

    for (int i = 0; i < event_count; i++) {

        if (strstr(events[i].title, search_term) ||
            strstr(events[i].date, search_term) ||
            strstr(events[i].time, search_term) ||
            strstr(events[i].location, search_term) ||
            strstr(events[i].description, search_term)) {

            printf("\n Event Found \n");
            printf("ID: %d\n", events[i].id);
            printf("Title: %s\n", events[i].title);
            printf("Date: %s\n", events[i].date);
            printf("Time: %s\n", events[i].time);
            printf("Location: %s\n", events[i].location);
            printf("Description: %s\n", events[i].description);

            found++;
        }
    }

    if (found == 0) {
        printf("No matching events found\n");
    }
}