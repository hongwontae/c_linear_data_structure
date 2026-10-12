#include "ui.h"
#include "double_linked_list.h"


int main (void) {

    init_list();
    dummy_data_add();

    event_loop_run();

    release_list();

    return 0;
}