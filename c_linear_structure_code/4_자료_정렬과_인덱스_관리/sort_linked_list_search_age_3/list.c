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
    add_new_node(10, "hong", "010-8489-3121");
    add_new_node(20, "kim", "010-8489-3121");
    add_new_node(30, "ji", "010-8489-3121");
    add_new_node(40, "song", "010-8489-3121");
}

void init_2 (void) {
    add_new_node(7, "Park", "010-1234-3333");
    add_new_node(5, "Kim", "010-1234-3333");
    add_new_node(8, "Chang", "010-1234-3333");
    add_new_node(6, "Hoon", "010-1234-3333");
    add_new_node(8, "Jang", "010-1234-3333");
    add_new_node(8, "Jung", "010-1234-3333");
    add_new_node(7, "Choi", "010-1234-3333");
    add_new_node(7, "Chae", "010-1234-3333");
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

void copy_node_data (USERDATA * user1, USERDATA * user2) {
    user1->age = user2->age;
    strcpy(user1->name, user2->name);
    strcpy(user1->phone, user2->phone);
}

void swap_node (USERDATA * user1, USERDATA * user2) {
    USERDATA  tmp = * user1;
    copy_node_data(user1, user2);
    copy_node_data(user2, &tmp);
}

void sort_list_by_name () {

    USERDATA * p_tmp = global_head_node.p_next;
    USERDATA * p_selected = NULL;
    USERDATA * p_cmp = NULL;

    while (p_tmp != NULL && p_tmp != global_tail_node.p_prev) {

        p_selected = p_tmp;
        p_cmp = p_selected->p_next;

        while (p_cmp != NULL && p_cmp != &global_tail_node) {
            if (strcmp(p_selected->name, p_cmp->name) > 0) {
                p_selected = p_cmp;
            }

            p_cmp = p_cmp->p_next;
        }

        if (p_selected != p_tmp) {
            swap_node(p_selected, p_tmp);
        }

        p_selected = NULL;
        p_tmp = p_tmp->p_next;
    }


}


void sort_list_by_age (void) {

    if (is_empty()) {
        return ;
    }
    // sort_list_by_name처럼 더미 노드의 앞 노드부터 시작합니다.
    // p_selected는 바뀔 값, p_cmp는 이동할 값
    USERDATA * p_tmp = global_head_node.p_next;
    USERDATA * p_selected = NULL;
    USERDATA * p_cmp = NULL;

    // p_tmp 기준값이 널이 아니고 기준값이 더미 노드의 뒷 노드가 아니면 지속합니다.
    while (p_tmp != NULL && p_tmp != global_tail_node.p_prev) {
        
        // 기준값을 p_tmp를 받음
        // 기준값 다음 노드부터 비교해야 선택정렬
        p_selected = p_tmp;
        p_cmp = p_tmp->p_next;

        // 기준값 다음 노드가 널이 아니거나 더미 테일 노드가 아니어야 지속
        while (p_cmp != NULL && p_cmp != &global_tail_node) {
            // 기준값이 나이가 더 많으면 변경되어 변경된 노드가 기준값이 됨
            if (p_selected-> age > p_cmp->age) {
                p_selected = p_cmp;
            }
            // 다음 노드로 이동
            p_cmp = p_cmp->p_next;
        }

        // 만약 초기 기준값과 루프를 돌고 온 값이 같다면 -> if문이 true가 없었던것이라 if문 수행 x
        // 변경되었다면 swap
        if (p_tmp != p_selected) {
            swap_node(p_tmp, p_selected);
        }

        // p_selected는 초기화
        // p_tmp는 다음 노드로 이동
        p_selected = NULL;
        p_tmp = p_tmp->p_next;

    }

}


// 범위에 해당되는 노드 집합을 전달해주는 함수입니다.
void ** search_by_age_range (int min, int max, int * cnt) {
    
    // 현재로는 판단안됨 / 단 p_tmp는 더미 헤드 노드의 첫 부분 -> 실질적인 첫 노드
    *cnt = 0;
    USERDATA * p_min = NULL;
    USERDATA * p_max = NULL;
    USERDATA * p_tmp = global_head_node.p_next;

    // 노드가 더미 테일 노드가 아니라면 지속합니다.
    // 이 루프의 결과는 최소 나이를 가진 노드들 중 가장 먼저 저장되었던 노드를 p_min, p_max에 대입합니다.
    while (p_tmp != &global_tail_node) {

        // 첫 노드부터 검사를 시작합니다.
        // 현 노드의 나이가 최소값으로 받은 것보다 높거나 같다면 그 노드를 지역변수에 대입합니다.
        // p_min, p_max 둘 다 해당, 그리고 최소값 노드를 찾았으면 break;
        // 만약 못 찾았다면 지속해서 마지막 노드까지 돕니다. -> 더미 테일 노드면 멈춤
        if (p_tmp->age >= min) {
            // 범위를 입력할 떄 6, 6 이렇게 입력한 것을 대비하는 것입니다.
            p_min = p_tmp;
            p_max = p_tmp;
            break;
        }
        p_tmp = p_tmp->p_next;
    }

    // 만약 최소값 노드가 널이 아니라면 p_tmp을 최소값 다음 노드로 이동시킵니다.
    // 최소값 노드 다음부터 찾아야 최대값 노드를 찾을 수 있습니다.
    if (p_min != NULL) {
        p_tmp = p_min->p_next;
    // p_min이 널이라면 실질적인 첫 노드를 가져옵니다.
    // p_min이 NULL인 이유 -> 뒤 while문에서 min이 0이고 모든 노드들이 나이의 값이 0을 넘는다면? -> NULL입니다.
    } else {
        p_tmp = global_head_node.p_next;
    }

    // 기준값 노드 (정렬된 연결 리스트에서 최소값 다음 노드 (최소값 노드랑 값이 같을 수도 있습니다. 다만 절대 아래는 아닙니다.))
    // 그리고 1 1 1에서 두 번쨰도 아닙니다. -> while문에서 첫 번쨰 제일 낮은 노드를 구하는 로직이라서
    // p_tmp가 더미 테일 노드가 아니면 지속합니다.
    while (p_tmp != &global_tail_node) {
        // 기준 노드의 나이가 최소값보다 높거나 같거나 기준 노드가 최대값보다 적거나 같거나라면 p_max에 p_tmp를 대입합니다.
        // 한 번만 하고 끝나는게 아니라 계속 돌립니다. -> 결국 최대값 중에 가장 마지막 최대값 노드를 찾음
        // ** 6 6이 들어와도 >= <= 이렇게 검사해서 로직상 문제 없음
        if (p_tmp->age >= min && p_tmp->age <= max) {
            p_max = p_tmp;
        // 만약 max를 넘어버린다면 거기서 멈춥니다.
        } else if (p_tmp->age > max) {
            break;
        }
        p_tmp = p_tmp->p_next;
    }

    // p_min과 p_max가 NULL이 아니라면 해당 문을 수행합니다.
    if (p_min != NULL && p_max != NULL) {
        // 기준 노드는 최소값을 가진 노드입니다.
        USERDATA * p_tmp = p_min;

        int count = 1;

        // 기준 노드가 최대노드가 아니라면 지속합니다. -> 최대 노드가 될 때까지 돕니다.
        // p_min과 p_max 사이의 노드의 개수를 구합니다. -> count를 1로 초기화해서 제대로 구하기 가능
        while (p_tmp != p_max) {
            ++count;
            p_tmp = p_tmp->p_next;
        }

        // count는 출력할 떄 필요해서 cnt를 주소로 받아서 넘겨줍니다.
        *cnt = count;

        
        // void *의 주소를 값으로 가지는 이중 포인터를 선언합니다.
        // 이 떄 void *를 값으로 갖는 배열의 수는 count입니다. -> 즉, 최소 ~ 최대 노드 개수
        void ** p_node_ptr_list = malloc(sizeof(void *) * count);

        // p_min은 최소 노드
        p_tmp = p_min;

        int i = 0;

        // 최소 노드부터 시작해서 지속적으로 앞으로 나아갑니다.
        // 앞으로 나아가는 값이 최대 노드와 같다면 정지합니다.
        for (; p_tmp != p_max; ++i) {
            p_node_ptr_list[i] = p_tmp;
            p_tmp = p_tmp->p_next;
        }

        // 마지막 노드에 최대 값 노드를 추가하고 return 합니다.
        p_node_ptr_list[i] = p_max;

        return p_node_ptr_list;

    }

    return NULL;

}
