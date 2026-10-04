#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct USERDATA {

    int age;
    char name [32];
    char phone [32];
    struct USERDATA * p_prev;
    struct USERDATA * p_next;

} USERDATA;


USERDATA global_head_node = {0, "Dummy_Head", "010-0000-0000", NULL};
USERDATA global_tail_node = {0, "Dummy_Tail", "010-0000-0000", NULL};

void connect_double_linked_list () {
    global_head_node.p_next = &global_tail_node;
    global_tail_node.p_prev = &global_head_node;
}

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

void forward_print_node () {

    printf("forward print\n");

    USERDATA * head_node = &global_head_node;

    while (head_node != NULL) {
        printf("[Current Address : %p] name : %s, age : %d, phone : %s, [Next Address : %p] \n",
            head_node, head_node->name, head_node->age, head_node->phone, head_node->p_next
        );
        head_node = head_node->p_next;
    }

    printf("\n");

}

void backward_print_node () {

    printf("backward print \n");

    USERDATA * tail_node = &global_tail_node;

    while (tail_node != NULL) {
        printf("[Current Address : %p] name : %s, age : %d, phone : %s, [Back Address : %p] \n",
            tail_node, tail_node->name, tail_node->age, tail_node->phone, tail_node->p_prev
        );

        tail_node = tail_node->p_prev;
    }

    printf("\n");

}

void init () {
    add_new_node(10, "hong", "010-8489-3121");
    add_new_node(20, "kim", "010-8489-3121");
    add_new_node(30, "ji", "010-8489-3121");
    add_new_node(40, "song", "010-8489-3121");
}

void clear_node () {
    
    USERDATA * head_node_refine = global_head_node.p_next;

    printf("clear_node\n");

    while (head_node_refine != NULL && head_node_refine->p_next != NULL) {

        USERDATA * back_up = head_node_refine->p_next;
        printf("clear 작업 중.. 주소 : %p, 이름 %s\n", head_node_refine, head_node_refine->name);
        free(head_node_refine);
        head_node_refine = back_up;

    }

    printf("\n");

}

USERDATA * search_node (char * name) {

    USERDATA * head_node = &global_head_node;

    while (head_node != NULL) {

        if (strcmp(head_node->name, name) == 0) {
            printf("Found!\n");
            printf("주소 : %p, 이름 : %s\n", head_node, head_node->name);
            return head_node;
        }

        head_node = head_node->p_next;
    }

    printf("%s에 해당되는 노드가 없습니다.\n", name);

    return NULL;

}

void remove_node (USERDATA * user) {

    printf("remove!");

    USERDATA * next_node = user->p_next;
    USERDATA * back_node = user->p_prev;

    next_node->p_prev = back_node;
    back_node->p_next = next_node;

    printf("");

    free(user);


}

void push_node (USERDATA * user) {

    USERDATA * new_node = malloc (sizeof (USERDATA));
    memcpy(new_node, user, sizeof(USERDATA));
    new_node->p_next = NULL;
    new_node->p_prev = NULL;

    // push_node가 next node로
    USERDATA * head_node = &global_head_node;
    USERDATA * head_node_next = head_node->p_next;

    head_node->p_next = new_node;
    new_node->p_prev = head_node;

    new_node->p_next = head_node_next;
    head_node_next->p_prev = new_node;

}

int is_empty (void) {
    if (global_head_node.p_next == &global_tail_node) {
        return 1;
    } 
    return 0;
}

USERDATA * pop_node () {

    if (is_empty()) {
        puts("Error : Stack UnderFlow.");
        return NULL;
    }

    USERDATA * pop = global_head_node.p_next;

    global_head_node.p_next = pop->p_next;
    pop->p_next->p_prev = pop->p_prev;

    return pop;



}

int main () {

    connect_double_linked_list();

    USERDATA user_1 = {0, "test-01", "0000", NULL, NULL};
    USERDATA user_2 = {0, "test-02", "0000", NULL, NULL};
    USERDATA user_3 = {0, "test-03", "0000", NULL, NULL};

    push_node(&user_1);
    push_node(&user_2);
    push_node(&user_3);

    forward_print_node();

    for (int i = 0; i < 3; ++i) {
        USERDATA * user = pop_node();
        printf("Pop : %s, %p\n", user->name, user);
        free(user);
    }

    printf("\n");


    clear_node();


    return 0;
}