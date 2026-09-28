#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct USERDATA
{

    int age;
    char name[32];
    char phone[32];
    struct USERDATA *p_next;

} USERDATA;

USERDATA *global_head_node = NULL;

void add_node(const char *name, const int age, const char *phone)
{

    USERDATA *new_node = malloc(sizeof(USERDATA));

    new_node->age = age;
    strcpy(new_node->name, name);
    strcpy(new_node->phone, phone);
    new_node->p_next = NULL;

    USERDATA *head_add_node = global_head_node;

    if (head_add_node == NULL)
    {
        global_head_node = new_node;
    }
    else
    {
        while (head_add_node != NULL)
        {
            if (head_add_node->p_next == NULL)
            {
                head_add_node->p_next = new_node;
                break;
            }
            head_add_node = head_add_node->p_next;
        }
    }

    printf("Add Success [name %s, age %d]\n", name, age);
}

void init()
{
    add_node("Hong", 10, "010-9999-3333");
    add_node("Kim", 20, "010-8888-3333");
    add_node("Ji", 30, "010-7777-3333");
    add_node("Jang", 40, "010-6666-3333");
    add_node("Land", 50, "010-5555-3333");
    add_node("OPks", 60, "010-4444-3333");
}

void print_node()
{

    USERDATA *print_head_node = global_head_node;

    while (print_head_node != NULL)
    {
        printf("[Current Address : %p] name : %s, age %d, phone : %s, [Next Address : %p]\n",
               print_head_node, print_head_node->name, print_head_node->age, print_head_node->phone, print_head_node->p_next);

        print_head_node = print_head_node->p_next;
    }

    printf("\n");
}

void clear_node()
{
    USERDATA *head_clear_node = global_head_node;

    while (head_clear_node != NULL)
    {
        USERDATA *temp;
        temp = head_clear_node->p_next;
        free(head_clear_node);
        head_clear_node = temp;
    }

    global_head_node = NULL;
}

void search_node(char *name)
{

    USERDATA *search_head_node = global_head_node;

    USERDATA *search_result = NULL;

    while (search_head_node != NULL)
    {
        if (strcmp(search_head_node->name, name) == 0)
        {
            search_result = search_head_node;
            break;
        }
        search_head_node = search_head_node->p_next;
    }
    if (search_result != NULL)
    {
        printf("Found!\n");
        printf("[Current Address : %p] name : %s, age : %d, phone : %s, [Next Address : %p]\n",
               search_result, search_result->name, search_result->age, search_result->phone, search_result->p_next);
    }
    else
    {
        printf("Not Found!\n");
    }
}

void delete_node(char *name)
{

    USERDATA *current_node = global_head_node;
    USERDATA *prev_node = NULL;

    while (current_node != NULL)
    {

        if (strcmp(current_node->name, name) == 0)
        {
            if (prev_node == NULL)
            {
                printf("Delete Success, name -> %s\n", current_node->name);
                global_head_node = current_node->p_next;
                free(current_node);
            }
            else
            {
                printf("Delete Success, name -> %s\n", current_node->name);
                prev_node->p_next = current_node->p_next;
                free(current_node);
                return;
            }
        }

        prev_node = current_node;
        current_node = current_node->p_next;
    }
}

int main(void)
{

    init();
    print_node();
    search_node("Kim");
    search_node("KKK");
    delete_node("Kim");
    delete_node("Hong");
    print_node();
    clear_node();

    return 0;
}