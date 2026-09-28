#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct USERDATA {

    int age;
    char name [32];
    char phone [32];
    struct USERDATA * p_next;

} USERDATA;

USERDATA * global_head_node = NULL;

void add_node (int age, char * name, char * phone) {

    USERDATA * user = malloc (sizeof(USERDATA));

    user->age = age;
    strcpy(user->name, name);
    strcpy(user->phone, phone);
    user->p_next = NULL;

    USERDATA * add_head_node = global_head_node;

    if (add_head_node == NULL) {
        global_head_node = user;
    } else {
        while (add_head_node != NULL) {
            if (add_head_node->p_next == NULL) {
                break;
            }
            add_head_node = add_head_node->p_next;
        }

        add_head_node->p_next = user;
    }


}

void print_all_node () {

    USERDATA * print_head_node = global_head_node;

   while (print_head_node != NULL) {
        printf("[Current Address : %p] name : %s, age : %d, phone : %s, [Next Address : %p] \n",
        print_head_node, print_head_node->name, print_head_node->age, print_head_node->phone, print_head_node->p_next
    );

        print_head_node = print_head_node->p_next;
   }

   printf("\n");

}

void init () {
    add_node(10, "Hong", "010");
    add_node(20, "Hoon", "031");
    add_node(30, "Kim", "081");
    add_node(40, "park", "119");
}

void clear_node () {
    USERDATA * clear_head_node = global_head_node;

    while (clear_head_node != NULL) {
        USERDATA * temp = clear_head_node;
        clear_head_node = clear_head_node->p_next;
        free(temp);
    }

    global_head_node = NULL;
}

void search_address_print (char * target) {

    printf("target : %s\n", target);

    USERDATA * search_head_node = global_head_node;

    int boolean = 0;

    while (search_head_node != NULL) {
        if (strcmp(target, search_head_node->name) == 0) {
            boolean = 1;
            printf("Found!\n [Current Address : %p] name : %s, age : %d, phone : %s, [Next Address : %p]",
                search_head_node, search_head_node->name, search_head_node->age, search_head_node->phone, search_head_node->p_next
            );
        } 
        search_head_node = search_head_node->p_next;
    }

    if (!boolean) {
        printf("Not Found!\n");
    }

    printf("\n");

}

void delete_node(char *target)
{
    USERDATA *current = global_head_node;
    USERDATA *prev = NULL;

    while (current != NULL) {

        if (strcmp(current->name, target) == 0) {

            // 첫 번째 노드인 경우
            if (prev == NULL) {
                global_head_node = current->p_next;
            }

            // 두 번째 이후 노드인 경우
            else {
                prev->p_next = current->p_next;
            }

            free(current);
            return;
        }

        prev = current;
        current = current->p_next;
    }

    printf("삭제할 노드를 찾지 못했습니다.\n");
}

int main (void) {

    init();
    print_all_node();
    search_address_print("Hong");
    search_address_print("KKK");
    delete_node("Hong");
    delete_node("Hong");
    delete_node("H");


    return 0;
}