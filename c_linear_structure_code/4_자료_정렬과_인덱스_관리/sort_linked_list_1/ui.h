typedef enum MY_MENU {EXIT, NEW, SEARCH, F_PRINT, B_PRINT, REMOVE} MY_MENU;

MY_MENU print_menu (void);
void event_loop_run (void);
void forward_print_node (void);
void backward_print_node (void);
void search (void);
void add (void);
void dele (void);