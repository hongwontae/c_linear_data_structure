#pragma once

typedef struct USERDATA {

    char name [32];
    int age;
    char phone [32];
    struct USERDATA * p_next;
    struct USERDATA * p_prev;

} USERDATA;

extern USERDATA global_head_node;
extern USERDATA global_tail_node;
extern USERDATA ** index_age;
extern USERDATA ** index_name;

unsigned int get_total_node_count (void);
int is_empty (void);
void release_list (void);
void init_list(void);
unsigned int re_count_node(void);
void UpdateIndexAll(void);
USERDATA** make_index_age (unsigned int* cnt );
USERDATA** make_index_name (unsigned int* cnt );
void dummy_data_add (void);
void add_new_node(int age, char *name, char *phone);

void node_data_switch (USERDATA * data_1, USERDATA * data_2);
void swap_node (USERDATA * user_1, USERDATA * user_2);
void sort_list_by_name (void);
void sort_list_by_age (void);
int search_list_by_name(USERDATA* user, char* name);
int search_list_by_phone (USERDATA * user, char * phone);
int search_list_by_age(int age);
int remove_by_name(char* name);

void** search_by_age_range(int min, int max, int* count);