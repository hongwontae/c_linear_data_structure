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

USERDATA * global_head_node = NULL;

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
    add_new_node(14, "Hoon", "010-8489-3121");
    add_new_node(14, "Kim", "010-8489-3121");
    add_new_node(14, "Hong", "010-8489-3121");
    add_new_node(14, "Lang", "010-8489-3121");
    add_new_node(40, "Jang", "010-8489-3121");
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

void print_node () {

    USERDATA * print_head_node = global_head_node;

        while (print_head_node != NULL)
    {
        printf("[Current Addess : %p] name : %s, age : %d, phone : %s, [Next Address : %p] \n",
            print_head_node, print_head_node->name, print_head_node->age, print_head_node->phone, print_head_node->p_next);

        print_head_node = print_head_node->p_next;
    }
    printf("\n");
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

USERDATA * search_to_remove (USERDATA ** pp_prev, const char * name) {

    USERDATA * p_current = global_head_node;
    USERDATA * p_prev = NULL;

    while (p_current != NULL) {
        if (strcmp(p_current->name, name) == 0) {
            *pp_prev = p_prev;
            return p_current;
        }
        p_prev = p_current;
        p_current = p_current->p_next;
    }

    return NULL;

}

void remove_node (USERDATA * p_previous) {

    USERDATA * p_remove = NULL;

    if (p_previous == NULL) {
        if (global_head_node == NULL) {
            return;
        } else {
            p_remove = global_head_node;
            global_head_node = p_remove->p_next;
            printf("remove_node -> %s\n", p_remove->name);
            free(p_remove);
        }

        return ;
    }

    p_remove = p_previous->p_next;
    p_previous->p_next = p_remove->p_next;
    free(p_remove);

}

void test_stop_01 () {

}

int main(void)
{   

    initial_add_user();

    print_node();

    USERDATA * pPrev = NULL;
    if (search_to_remove(&pPrev, "Hooun") != NULL) {
        remove_node(pPrev);
    } else {
        printf("name과 일치하는 노드가 없어서 삭제할 수 없습니다.\n");
    }


    print_node();
    
    clear_node();

    return 0;
}