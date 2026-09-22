// 사실 Stack 구조입니다. -> input과 output이 다른 방향입니다.


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct USERDATA {

    int age;
    char name [32];
    char phone [32];
    struct USERDATA * p_next;

} USERDATA;

USERDATA * global_head_node = NULL;

void add_new_node (const char my_string [], const int age, const char phone_number []) {

    USERDATA * new_node = (USERDATA *) malloc(sizeof(USERDATA));


    // 데이터 추가 
    new_node->age = age;
    strcpy(new_node->name, my_string);
    strcpy(new_node->phone, phone_number);
    new_node->p_next = NULL;

    if (global_head_node == NULL) {
        global_head_node = new_node;
    } else {
        new_node->p_next = global_head_node;
        global_head_node = new_node;
    }
    

};

void initial_data_add () {
    add_new_node("Hello-kkk", 10, "010-2c22-1111");
    add_new_node("Hello-bbb", 20, "010-1422-11ss");
    add_new_node("Hello-ccc", 30, "010-2452-1141");
    add_new_node("Hello-ddd", 40, "010-22ff-11as");
}

void node_clear () {

    USERDATA * clear_p_head_node = global_head_node;
    USERDATA * back_up = NULL;

    while (clear_p_head_node != NULL) {
        back_up = clear_p_head_node->p_next;

        printf("Delete Node : [Current Address%p] name : %s, [Next Address %p]\n",
             clear_p_head_node, clear_p_head_node->name, clear_p_head_node->p_next);

        free(clear_p_head_node);
        clear_p_head_node = back_up;
    }

}


int main (void) {

    initial_data_add();

    USERDATA * main_head_node = global_head_node;

    while (main_head_node != NULL) {
        
        printf("[Current Address %p] name : %s, age : %d, phone : %s, Next Address : %p \n",
            main_head_node, main_head_node->name, main_head_node->age, main_head_node->phone, main_head_node->p_next
        );

        main_head_node = main_head_node->p_next;
    }
    node_clear();


    return 0;
}