#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "ui.h"


MY_MENU print_menu (void) {

    MY_MENU input = 0;

    printf("[1] New\t[2] Search\t[3] F_Print\t[4] B_Print\t[5] Remove\t[0] Exit\n");
    scanf("%d%*c", &input);
    return input;
}

void event_loop_run (void) {
    MY_MENU menu = 0;

    while ((menu = print_menu()) != 0) {
        switch (menu) {

            case NEW :
                add();
                break;
            
            case SEARCH :
                search_by_age();
                break;
            
            case F_PRINT :
                forward_print_node();
                break;
            
            case B_PRINT :
                backward_print_node();
                break;
            
            case REMOVE :
                dele();
                break;
            
            default :
            break;
        }
    }

    printf("bye!\n");

}

void forward_print_node (void) {

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

void backward_print_node (void) {

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

void search (void) {

    char name [32];
    scanf("%s", name);

    USERDATA * user = search_node(name);

    if (user != NULL) {
        printf("Found!\n");
        printf("이름 : %s, 나이 : %d, 전화번호 : %s\n", user->name, user->age, user->phone);
    } else {
        printf("Not Found!\n");
    }

}

void add (void) {
    char name [32];
    char phone [32];
    int age;

    printf("enter the name\n");
    scanf("%s", name);
    printf("\n");

    printf("enter the phone\n");
    scanf("%s", phone);
    printf("\n");

    printf("enter the age\n");
    scanf("%d", &age);
    printf("\n");

    add_new_node(age, name, phone);
    

}

void dele (void) {

    char name [32];

    printf("enter the removed name\n");
    scanf("%s", name);

    USERDATA * user = search_node(name);

    if (user != NULL) {
        remove_node(user);
    } else {
        printf("삭제할 유저가 없습니다.\n");
    }

    printf("\n");
}

void search_by_age (void) {

    int min = 0, max = 1;

    int cnt = 0;

    printf("Index search MIN MAX age : ");
    scanf("%d%d%*c", &min, &max);

    sort_list_by_age();

    // min, max는 초기화 / sort_list_by_age로 인해서 나이순으로 정렬 완료 (오름차순)


    void ** p_result = search_by_age_range(min, max, &cnt);
    USERDATA * p_tmp = NULL;

    // 전달된 값은 현재 갖춰진 이중 연결리스트의 실체의 일부분 배열입니다.
    for (int i = 0; i < cnt; ++i) {
        p_tmp = (USERDATA *) p_result[i];
        printf("%d, %s, %s\n", p_tmp->age, p_tmp->name, p_tmp->phone);
    }

    free(p_result);
    

}
