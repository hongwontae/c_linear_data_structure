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
    add_new_node(10, "Kim", "010-8489-3121");
    add_new_node(20, "Hoon", "010-8489-3121");
    add_new_node(30, "Choi", "010-8489-3121");
    add_new_node(40, "Jang", "010-8489-3121");
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

void node_data_copy (USERDATA * p_left, USERDATA * p_right) {
    p_left->age = p_right->age;
    strcpy(p_left->name, p_right->name);
    strcpy(p_left->phone, p_right->phone);
}

void swap_node (USERDATA * p_left, USERDATA * p_right) {
    USERDATA tmp = * p_left;
    node_data_copy(p_left, p_right);
    node_data_copy(p_right, &tmp);
}

void sort_list_by_name (void) {
    
    if (is_empty()) {
        return;
    }

    USERDATA * p_tmp = global_head_node.p_next;
    USERDATA * p_selected = NULL;
    USERDATA * p_cmp = NULL;

    // 첫 노드를 더미 앞에 노드라고 가정
    // while을 한 번이라도 돌 수 있으려면 첫 노드 하나만 존재해서는 안됩니다.
    // 즉, while문을 통과하면 실 노드는 2개 이상입니다.
    while (p_tmp != NULL && p_tmp != global_tail_node.p_prev) {

        // p_selected는 현 노드
        // p_cmp는 현 노드의 다음 노드
        p_selected = p_tmp;
        p_cmp = p_tmp->p_next;

        while (p_cmp != NULL && p_cmp != &global_tail_node) {
            // strcmp > 0 str1이 str2보다 사전순으로 뒤에 존재
            // strcmp < 0 str1이 str2보다 사전순으로 앞섬
            if (strcmp(p_selected->name, p_cmp->name) > 0) {
                p_selected = p_cmp;
            }
            // 첫 노드를 제외한 모든 요소를 돕니다.
            // 이 떄 while문으로 
            p_cmp = p_cmp->p_next;
        }

        if (p_tmp != p_selected) {
            swap_node(p_tmp, p_selected);
        }

        p_selected = NULL;
        p_tmp = p_tmp->p_next;

    }

}


