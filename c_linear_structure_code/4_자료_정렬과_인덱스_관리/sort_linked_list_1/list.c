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

// p_left값을 먼저 바꿉니다. -> 이 떄 p_left값을 right에 들어가야 하는데 데이터가 유실되면 안됩니다.
// 그래서 tmp를 둬서 데이터를 백업합니다.
void swap_node (USERDATA * p_left, USERDATA * p_right) {
    USERDATA tmp = * p_left;
    node_data_copy(p_left, p_right);
    node_data_copy(p_right, &tmp);
}

void sort_list_by_name (void) {
    
    // 1. is_empty()를 통해 헤드 노드의 앞 노드가 tail_node인지 확인합니다.
    // 다시 말해서 더미 헤드 노드의 앞이 더미 테일 노드인지 확인하는 함수입니다. 만약 true라면 return합니다.
    if (is_empty()) {
        return;
    }

    // 2.루프가 처음 돌 떄 p_tmp는 실질적인 첫 노드입니다. (더미 노드 다음)
    // p_selected = NULL; / p_cmp = NULL;
    USERDATA * p_tmp = global_head_node.p_next;
    USERDATA * p_selected = NULL;
    USERDATA * p_cmp = NULL;


    // 3. 첫 노드가 NULL 아니고 첫 노드가 더미 테일 노드의 뒤가 아니라면 지속적으로 실행합니다.
    // 즉, 초기 연결 리스트가 head_node - node - tail_node라면 진입할 수 없습니다. (is_empty는 통과합니다.)
    // 그리고 내부적으로 기준 노드는 지속적으로 앞으로 가는 것을 생각해볼 떄 p_tmp가 더미 테일 노드의 전 노드라면 더 이상 while을 실행할 이유가 없습니다.
    while (p_tmp != NULL && p_tmp != global_tail_node.p_prev) {

        
        // 4. p_tmp는 while전에 선언 및 정의했고 p_selected에 대입했습니다.
        // p_selected는 노드를 받고 비교시에 교체되는 노드라고 생각해야 합니다.
        // p_cmp는 p_selected의 앞 노드입니다. -> 기준 노드와 그 앞의 노드 전부를 비교해야 합니다. -> p_cmp는 while문에서 지속적으로 교체됩니다.
        // 즉, 해당 첫 while문 정하는 노드는 가장 작은 노드 / 그 다음 while은 그 다음 작은 노드
        p_selected = p_tmp;
        p_cmp = p_tmp->p_next;

        // 5. p_cmp가 NULL이 아니어야 하고, p_cmp는 더미 테일 노드가 아니어야 지속적으로 실행됩니다.
        while (p_cmp != NULL && p_cmp != &global_tail_node) {

            // 6. 여기서 기준 노드의 이름과 기준 노드 다음의 노드를 비교합니다.
            // 7. 만약 if문이 true라면 기준 노드를 바꿉니다.
            if (strcmp(p_selected->name, p_cmp->name) > 0) {
                p_selected = p_cmp;
            }

            // p_cmp는 기준 노드의 다음 노드 / 지속적으로 기준 노드의 다음 노드의 다음 노드.. 기준 노드의 다음 노드의 다음 노드의 다음 노드..
            p_cmp = p_cmp->p_next;
        }

        // 8. while문 작업을 했는데 애초에 기준 노드가 제일 작았다면 p_tmp과 p_selected는 같았기에 아무런 동작도 하지 않게 합니다.
        // 만약 다르다면 swap_node로 데이터만 변경하는 함수를 실행합니다.
        if (p_tmp != p_selected) {
            swap_node(p_tmp, p_selected);
        }

        // 명시적으로 p_selected를 null로 만듭니다. -> 없어도 됩니다. p_selected는 p_tmp로 대입됩니다.
        // p_tmp인 기준요소가 그 다음으로 가야합니다. -> 가장 작은 수를 찾았고 그 다음 작은 수를 찾으러 가는 길입니다.
        p_selected = NULL;
        p_tmp = p_tmp->p_next;

    }

}


