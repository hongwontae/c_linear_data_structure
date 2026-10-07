#pragma

typedef struct USERDATA {

    int age;
    char name [32];
    char phone [32];
    struct USERDATA * p_prev;
    struct USERDATA * p_next;

} USERDATA;

USERDATA global_head_node;
USERDATA global_tail_node;

void add_new_node (int age, const char * name, const char * phone);
void connect_double_linked_list (void);
void clear_node (void);
void enqueue (USERDATA * user);
USERDATA * dequeue (void);
USERDATA * pop_node (void);
void push_node (USERDATA * user);
void init (void);
int is_empty (void);
USERDATA * search_node (char * name);
void remove_node (USERDATA * user);
void copy_node_data (USERDATA * user1, USERDATA * user2);
void swap_node (USERDATA * user1, USERDATA * user2);
void sort_list_by_name (void);