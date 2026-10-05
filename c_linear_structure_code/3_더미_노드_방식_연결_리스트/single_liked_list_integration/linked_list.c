#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "ui.h"

int main () {

    connect_double_linked_list();
    init();
    event_loop_run();

    printf("\n");
    clear_node();
    return 0;
}