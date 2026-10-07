#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "ui.h"
#include "test.h"

int main () {

    connect_double_linked_list();
    init_2();
    event_loop_run();
    clear_node();


    return 0;
}