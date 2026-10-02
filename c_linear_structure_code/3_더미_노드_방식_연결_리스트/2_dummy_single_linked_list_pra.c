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
    add_new_node(10, "kim", "010-8489-3121");
    add_new_node(10, "ji", "010-8489-3121");
    add_new_node(10, "song", "010-8489-3121");
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

USERDATA * search_node (char * name) {

    USERDATA * head_node = &global_head_node;

    while (head_node != NULL) {
        if (strcmp(head_node->name, name) == 0) {
            printf("found!\n");
            printf("[Current Address : %p] name : %s\n", head_node, head_node->name);
            return head_node;
        }
        head_node = head_node -> p_next;
    }

    printf("전달받은 이름에 해당하는 노드가 없습니다.\n");

    return NULL;

}

USERDATA * prev_remove_node (char * name) {
    USERDATA * head_node = &global_head_node;

    while (head_node->p_next != NULL) {
        if (strcmp(head_node->p_next->name, name) == 0) {
            printf("삭제할 전 노드를 찾았습니다. 이름 : %s \n", head_node->name);
            return head_node;
        }

        head_node = head_node->p_next;
    }

    printf("전달받은 이름에 해당되는 삭제할 노드가 없습니다.\n");

    return NULL;

}

void remove_node (USERDATA * prev) {

    USERDATA * remove_node = prev->p_next;

    prev->p_next = remove_node->p_next;

    printf("해당 %s 노드를 삭제했습니다.\n", remove_node->name);
    free(remove_node);

}

int main (void) {


    init();
    print_node();

    USERDATA * user1 = prev_remove_node("hong");
    if (user1 != NULL) {
        remove_node(user1);
    } 

    USERDATA * user2 = prev_remove_node("hong");
        if (user2 != NULL) {
        remove_node(user2);
    } 

    USERDATA * user3 = prev_remove_node("ji");
        if (user3 != NULL) {
        remove_node(user3);
    } 

    USERDATA * user4 = prev_remove_node("kk");
        if (user4 != NULL) {
        remove_node(user4);
    } 



    print_node();

    printf("\n");

    clear_node();


    return 0;
}