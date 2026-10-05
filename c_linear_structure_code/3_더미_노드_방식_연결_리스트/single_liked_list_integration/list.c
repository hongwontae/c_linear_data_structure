#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


USERDATA global_head_node = {0, "Dummy_Head", "010-0000-0000"};
USERDATA global_tail_node = {0, "Dummy_Tail", "010-0000-0000"};

void add_new_node (int age, const char * name, const char * phone) {

    USERDATA * new_node = malloc (sizeof (USERDATA));
    new_node->age = age;
    strcpy(new_node->name, name);
    strcpy(new_node->phone, phone);
    new_node->p_prev = NULL;
    new_node->p_next = NULL;

    USERDATA * tail_node = &global_tail_node;

    USERDATA * prev_node = tail_node->p_prev;

    prev_node->p_next = new_node;
    tail_node->p_prev = new_node;

    new_node->p_prev = prev_node;
    new_node->p_next = tail_node;

}


void connect_double_linked_list (void) {
    global_head_node.p_next = &global_tail_node;
    global_tail_node.p_prev = &global_head_node;
}

void clear_node (void) {
    
    USERDATA * head_node_refine = global_head_node.p_next;


    while (head_node_refine != NULL && head_node_refine->p_next != NULL) {

        USERDATA * back_up = head_node_refine->p_next;
        free(head_node_refine);
        head_node_refine = back_up;

    }


}

void enqueue (USERDATA * user) {
    return add_new_node(user->age, user->name, user->phone);
}

USERDATA * dequeue (void) {
    return pop_node();
}

USERDATA * pop_node (void) {

    if (is_empty()) {
        return NULL;
    }

    USERDATA * pop = global_head_node.p_next;

    global_head_node.p_next = pop->p_next;
    pop->p_next->p_prev = pop->p_prev;

    return pop;

}

void push_node (USERDATA * user) {

    USERDATA * new_node = malloc (sizeof (USERDATA));
    memcpy(new_node, user, sizeof(USERDATA));
    new_node->p_next = NULL;
    new_node->p_prev = NULL;

    USERDATA * head_node = &global_head_node;
    USERDATA * head_next_node = head_node->p_next;

    new_node->p_prev = &global_head_node;
    new_node->p_next = global_head_node.p_next;

    head_next_node->p_prev = new_node;
    global_head_node.p_next = new_node;


}

void init (void) {
    add_new_node(10, "hong", "010-8489-3121");
    add_new_node(20, "kim", "010-8489-3121");
    add_new_node(30, "ji", "010-8489-3121");
    add_new_node(40, "song", "010-8489-3121");
}

int is_empty (void) {
    if (global_head_node.p_next == &global_tail_node) {
        return 1;
    } 
    return 0;
}

USERDATA * search_node (char * name) {

    USERDATA * head_node = &global_head_node;

    while (head_node != NULL) {

        if (strcmp(head_node->name, name) == 0) {
            return head_node;
        }

        head_node = head_node->p_next;
    }

    return NULL;

}

void remove_node (USERDATA * user) {

    USERDATA * next_node = user->p_next;
    USERDATA * back_node = user->p_prev;

    next_node->p_prev = back_node;
    back_node->p_next = next_node;

    free(user);


}

