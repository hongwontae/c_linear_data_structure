#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct USERDATA
{
    int age;
    char name[32];
    char phone[20];
    struct USERDATA *p_next;
} USERDATA;

USERDATA *g_p_head = NULL;

void add_new_node(const int age, const char name[32], const char phone[32])
{

    USERDATA *new_node = (USERDATA *)malloc(sizeof(USERDATA));

    new_node->age = age;
    strcpy(new_node->name, name);
    strcpy(new_node->phone, phone);

    if (g_p_head == NULL)
    {
        g_p_head = new_node;
    }
    else
    {
        new_node->p_next = g_p_head;
        g_p_head = new_node;
    }
}

void init_node()
{
    add_new_node(10, "jj", "10222");
    add_new_node(20, "3333", "dkdkdkd");
    add_new_node(30, "dkdk", "-010101");
}

void node_clear () {
    
    USERDATA * p_head = g_p_head;

    USERDATA * back_up;

    while (p_head != NULL) {
        
        back_up = p_head->p_next;

        printf("Delete [%p] age : %d, name : %s, next add : %p\n",
            p_head, p_head->age, p_head->name, p_head->p_next
        );

        free(p_head);

        p_head = back_up;
    }


}

int main(void)
{

    init_node();

    USERDATA *p_head = g_p_head;

    while (p_head != NULL)
    {
        printf("[%p] age : %d, name : %s, phone : %s, next address : %p\n",
               p_head, p_head->age, p_head->name, p_head->phone, p_head->p_next);

        p_head = p_head->p_next;
    }

    node_clear();

    return 0;
}