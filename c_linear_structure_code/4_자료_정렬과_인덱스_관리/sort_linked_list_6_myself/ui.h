#pragma once

typedef enum MY_MENU
{
	EXIT, NEW, SEARCH, SEARCH_RANGE, PRINT, REMOVE
} MY_MENU;


MY_MENU PrintMenu(void);
void print_list(int wait);
void add_new_user(void);
void event_loop_run(void);
void search_by_name(void);
void search_by_name_to_remove(void);
void search_by_age(void);