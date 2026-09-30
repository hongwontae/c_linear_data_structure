#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct USERDATA {

    int age;
    char name [32];
    char phone [32];
    struct USERDATA * p_next;

} USERDATA;


USERDATA global_head_node = {0, "Dummy", "000-0000-0000", NULL};

void add_new_node (int age, char * name, char * phone) {

    USERDATA * new_node = malloc (sizeof(USERDATA));

    new_node->age = age;
    strcpy(new_node->name, name);
    strcpy(new_node->phone, phone);
    new_node->p_next = NULL;

    USERDATA * head_node = &global_head_node;

    while (head_node->p_next != NULL) {
        head_node = head_node->p_next;
    }

    head_node->p_next = new_node;

}

void init () {
    add_new_node(10, "hong", "010-8489-3121");
    add_new_node(10, "hong", "010-8489-3121");
    add_new_node(10, "hong", "010-8489-3121");
    add_new_node(10, "hong", "010-8489-3121");
}

void print_node () {

    USERDATA * head_node = &global_head_node;

    while (head_node != NULL) {
        printf("[Current Address : %p] name : %s, age : %d, phone : %s, [Next Address : %p] \n", 
            head_node, head_node->name, head_node->age, head_node->phone, head_node->p_next
        );
        head_node = head_node->p_next;
    }

    printf("\n");

}

void clear_node () {

    USERDATA * head_node = global_head_node.p_next;

    while (head_node != NULL) {

        USERDATA * next_address = head_node->p_next;

        printf("free 작업 중.. 현 주소 : %p, 이름 : %s 다음 주소 : %p\n", head_node, head_node->name, next_address );

        free(head_node);

        head_node = next_address;

    }
    
    printf("\n");

}

int main (void) {


    init();
    print_node();
    clear_node();


    return 0;
}