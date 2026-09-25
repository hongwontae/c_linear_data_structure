#include <stdio.h>


typedef struct USERDATA {

    int age;
    char name [32];
    char phone [30];
    struct USERDATA * pNext;

} USERDATA;


int main (void) {

    USERDATA u_group [4] = {
        {10, "Hello-akak", "010-8393-3121", NULL},
        {10, "Hello-wowo", "010-4232-4444", NULL},
        {10, "Hello-bkbk", "010-3244-2222", NULL},
        {10, "Hello-azaz", "010-8653-1111", NULL},
    };

    size_t length = sizeof(u_group) / sizeof(u_group[0]);

    // 각 노드는 현재 다음 주소의 값을 가지고 있지 않습니다.
    // 각 노드에 다음 주소를 넣겠습니다.

    for (int i = 0; i < length-1; ++i) {
        u_group[i].pNext = &u_group[i+1];
    }

    // 확인 절차
    for (int i = 0 ; i < length; ++i) {
        printf("u_grup[%d] pNext = %p\n", i, u_group[i].pNext);
    }


    // 생성한 싱글 리스트가 유효한지 판단합니다.
    USERDATA * p = u_group;

    while (p != NULL) {
        printf("age : %d, name : %s, phone : %s\n", p->age, p->name, p->phone);
        printf("해당 address : %p\n", p);
        printf("가리키고 있는 address : %p\n", p->pNext);
        p = p->pNext;
    }

 


} 