#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "ui.h"



void test_sort_list_01 (void) {

    printf("Test Sort List 01\n");

    add_new_node(5, "Hoon", "010-8489-3121");
    forward_print_node();
    sort_list_by_name();
    forward_print_node();
    clear_node();
    printf("test success\n");


}

void test_sort_list_02 (void) {

    printf("Test Sort List 02\n");

    add_new_node(6, "Hoon01", "010-8489-3121");
    add_new_node(5, "Hoon", "010-8489-3121");
    forward_print_node();
    sort_list_by_name();
    forward_print_node();
    clear_node();
    printf("test success\n");


}

void test_sort_list_03 (void) {

    printf("Test Sort List 03\n");

    add_new_node(6, "Hong01", "010-8489-3121");
    add_new_node(5, "Hong", "010-8489-3121");
    add_new_node(5, "Hoon", "010-8489-3121");
    forward_print_node();
    sort_list_by_name();
    forward_print_node();
    clear_node();
    printf("test success\n");


}

void test_sort_list_04 (void) {

    printf("Test Sort List 04\n");

    init();
    forward_print_node();
    sort_list_by_name();
    forward_print_node();
    clear_node();
    printf("test success\n");


}