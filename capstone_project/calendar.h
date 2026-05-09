#ifndef CALENDAR_H
#define CALENDAR_H

#define MAX_EVENTS 100
#define MAX_STRING 100
#define DATA_FILE "calendar_data.txt"

// event structure
typedef struct {
    int id;
    char title[MAX_STRING];
    char date[MAX_STRING];
    char time[MAX_STRING];
    char location[MAX_STRING];
    char description[MAX_STRING];
} Event;

// global variables
extern Event events[MAX_EVENTS];
extern int event_count;
extern int next_id;

// function declarations
void save_events();
void load_events();
void add_event();
void view_events();
void update_event();
void delete_event();
void search_events();

#endif