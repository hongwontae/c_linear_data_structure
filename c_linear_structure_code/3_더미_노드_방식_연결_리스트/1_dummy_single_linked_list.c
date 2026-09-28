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

USERDATA global_head_node = {0, "__Dummy Node__", "010-0000-0000", NULL};

void add_new_node (int age, char name [], char phone []) {

    USERDATA * new_node = (USERDATA *) malloc(sizeof(USERDATA));
    
    new_node->age = age;
    strcpy(new_node->name, name);
    strcpy(new_node->phone, phone);
    new_node->p_next = NULL;


    USERDATA * end_node = &global_head_node;

    while (end_node->p_next != NULL) {
            end_node = end_node->p_next;
        }

    end_node->p_next = new_node;
}

void initial_add_user () {
    add_new_node(14, "Hoon", "010-8489-3121");
    add_new_node(14, "Kim", "010-8489-3121");
    add_new_node(14, "Hong", "010-8489-3121");
    add_new_node(14, "Lang", "010-8489-3121");
    add_new_node(40, "Jang", "010-8489-3121");
}

void clear_node () {

    USERDATA * clear_node = global_head_node.p_next;
    USERDATA * back_up = NULL;

    while (clear_node != NULL) {
        back_up = clear_node->p_next;
        
        printf("삭제할 노드 : %p, 이름은 %s, 다음은 %p\n", clear_node, clear_node->name, clear_node->p_next);

        free(clear_node);

        clear_node = back_up;
    }

    global_head_node.p_next = NULL;
}

void print_node () {

    USERDATA * print_head_node = &global_head_node;

        while (print_head_node != NULL)
    {
        printf("[Current Addess : %p] name : %s, age : %d, phone : %s, [Next Address : %p] \n",
            print_head_node, print_head_node->name, print_head_node->age, print_head_node->phone, print_head_node->p_next);

        print_head_node = print_head_node->p_next;
    }
    printf("\n");
}

USERDATA * search_by_name (const char * search_name) {

    USERDATA * search_node = global_head_node.p_next;

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

USERDATA * search_to_remove (const char * name) {

    USERDATA * p_prev = &global_head_node;

    while (p_prev->p_next != NULL) {
        if (strcmp(p_prev->p_next->name, name) == 0) {
            return p_prev;
        }
        p_prev = p_prev->p_next;
    }

    return NULL;

}

void remove_node (USERDATA * p_prev) {

    USERDATA * p_remove = NULL;

    p_remove = p_prev->p_next;
    p_prev->p_next = p_remove->p_next;
    printf("remove_node -> %s\n", p_remove->name);
    free(p_remove);
}

int main(void)
{   

    initial_add_user();

    print_node();

    USERDATA * pPrev = search_to_remove("Hoon");
    if (pPrev != NULL) {
        remove_node(pPrev);
    } else {
        printf("name과 일치하는 노드가 없어서 삭제할 수 없습니다.\n");
    }


    print_node();
    
    clear_node();

    return 0;
}