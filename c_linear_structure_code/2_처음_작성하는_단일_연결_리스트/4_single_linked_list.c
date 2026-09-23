// 새 노드 추가하기 + 순차적으로 add

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct USERDATA
{

    int age;
    char name[30];
    char phone[30];
    struct USERDATA *p_next;

} USERDATA;

USERDATA *global_head_node = NULL;

void add_new_node (int age, char name [], char phone []) {
    USERDATA * new_node = (USERDATA *) malloc(sizeof(USERDATA));
    
    new_node->age = age;
    strcpy(new_node->name, name);
    strcpy(new_node->phone, phone);
    new_node->p_next = NULL;

    if (global_head_node == NULL) {
        global_head_node = new_node;
    } else {
        USERDATA * end_node = global_head_node;

        while (end_node->p_next != NULL) {
            end_node = end_node->p_next;
        }

        end_node->p_next = new_node;

    }

}

void initial_add_user () {
    add_new_node(14, "Hello", "010-8489-3121");
    add_new_node(14, "Hello", "010-8489-3121");
    add_new_node(14, "Hello", "010-8489-3121");
    add_new_node(14, "Hello", "010-8489-3121");
    add_new_node(40, "Zlatan", "010-8489-3121");
}

void clear_node () {

    USERDATA * clear_node = global_head_node;
    USERDATA * back_up = NULL;

    while (clear_node != NULL) {
        back_up = clear_node->p_next;
        
        printf("삭제할 노드 : %p, 이름은 %s, 다음은 %p\n", clear_node, clear_node->name, clear_node->p_next);

        free(clear_node);

        clear_node = back_up;
    }


}

USERDATA * search_by_name (const char * search_name) {
    USERDATA * search_node = global_head_node;

    while (search_node != NULL) {

        if (strcmp(search_node->name, search_name) == 0) {
            printf("%s FOUND!\n", search_node->name);
            return search_node;
        }

        search_node = search_node->p_next;
    }

    printf("%s NOT FOUND\n", search_name);

    return NULL;

}


int main(void)
{   

    initial_add_user();

    USERDATA *main_head_node = global_head_node;

    USERDATA * search = search_by_name("Zlatan");

    // printf("[%p] name : %s, age : %d, phone : %s [%p]\n",
    //     search, search->name, search->age, search->phone, search->p_next
    // );

    while (main_head_node != NULL)
    {
        printf("[Current Addess : %p] name : %s, age : %d, phone : %s, [Next Address : %p] \n",
            main_head_node, main_head_node->name, main_head_node->age, main_head_node->phone, main_head_node->p_next);

        main_head_node = main_head_node->p_next;
    }

    clear_node();

    return 0;
}