#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "double_linked_list.h"

USERDATA global_head_node = {"Dummy head node", 0, "000-0000-0000"};
USERDATA global_tail_node = {"Dummy tail node", 0, "000-0000-0000"};
USERDATA **index_age = NULL;
USERDATA **index_name = NULL;
static unsigned int g_total_node_count = 0;

unsigned int get_total_node_count(void)
{
    return g_total_node_count;
}

int is_empty(void)
{

    if (global_head_node.p_next == &global_tail_node)
    {
        return 1;
    }

    return 0;
}

void release_list(void)
{

    if (is_empty())
    {
        return;
    }

    USERDATA *standard_node = global_head_node.p_next;
    USERDATA *back_up_node = NULL;

    while (standard_node != &global_tail_node && standard_node != NULL)
    {

        back_up_node = standard_node->p_next;

        free(standard_node);

        standard_node = back_up_node;
    }

    global_head_node.p_next = &global_tail_node;
    global_tail_node.p_prev = &global_tail_node;
    g_total_node_count = 0;

    if (index_age != NULL)
    {
        free(index_age);
        index_age = NULL;
    }

    if (index_name != NULL)
    {
        free(index_name);
        index_name = NULL;
    }
}

void init_list(void)
{

    release_list();

    global_head_node.p_next = &global_tail_node;
    global_tail_node.p_prev = &global_head_node;
    g_total_node_count = 0;

    index_age = NULL;
    index_name = NULL;
}

unsigned int re_count_node(void)
{

    unsigned int cnt = 0;

    USERDATA *standard_node = global_head_node.p_next;

    while (standard_node != &global_tail_node)
    {
        ++cnt;
        standard_node = standard_node->p_next;
    }

    g_total_node_count = cnt;
    return cnt;
}

void add_new_node(int age, char *name, char *phone)
{

    USERDATA *user = calloc(1, sizeof(USERDATA));
    user->age = age;
    strcpy(user->name, name);
    strcpy(user->phone, phone);

    USERDATA *tail_node = &global_tail_node;
    user->p_next = tail_node;
    user->p_prev = tail_node->p_prev;

    tail_node->p_prev->p_next = user;
    tail_node->p_prev = user;

    ++g_total_node_count;

    UpdateIndexAll();
}

void dummy_data_add (void) {
    
	add_new_node(7, "Park", "010-1234-3333");
	add_new_node(5, "Kim", "010-1234-1111");
	add_new_node(8, "Chang", "010-1234-7777");
	add_new_node(6, "Hoon", "010-1234-2222");
	add_new_node(8, "Jang", "010-1234-6666");
	add_new_node(8, "Jung", "010-1234-8888");
	add_new_node(7, "Choi", "010-1234-4444");
	add_new_node(7, "Chae", "010-1234-5555");

}

void UpdateIndexAll(void)
{

    if (index_age != NULL)
    {
        free(index_age);
        index_age = NULL;
    }

    if (index_name != NULL)
    {
        free(index_name);
        index_name = NULL;
    }

    unsigned int cnt = 0;

    index_age = (USERDATA **)make_index_age(&cnt);
    index_name = (USERDATA **)make_index_name(&cnt);
}

USERDATA ** make_index_age (unsigned int * cnt) {

    *cnt = 0;

    if (is_empty()) {
        return NULL;
    }

    USERDATA ** age_list;

    age_list = malloc(sizeof(USERDATA *) * get_total_node_count());
    memset(age_list, 0, sizeof(USERDATA *) * get_total_node_count());

    *cnt = get_total_node_count();

    USERDATA * standard_node = global_head_node.p_next;

    int index_1 = 0;
    while (standard_node != &global_tail_node) {
        age_list[index_1] = standard_node;
        standard_node = standard_node->p_next;
        ++index_1;
    }

    for (int i = 0; i < get_total_node_count()-1; ++i) {

        for (int j = i+1; j < get_total_node_count(); ++j) {
            if (age_list[i]->age > age_list[j]->age) {
                USERDATA *temp = age_list[i];
                age_list[i] = age_list[j];
                age_list[j] = temp;
            }
        }
    }

    return age_list;


}

USERDATA ** make_index_name (unsigned int * cnt) {

    *cnt = 0;

    if (is_empty()) {
        return NULL;
    }

    USERDATA ** name_list;

    name_list = malloc(sizeof(USERDATA *) * get_total_node_count());
    memset(name_list, 0, sizeof(USERDATA *) * get_total_node_count());

    *cnt = get_total_node_count();

    USERDATA * standard_node = global_head_node.p_next;

    int index_1 = 0;
    while (standard_node != &global_tail_node) {
        name_list[index_1] = standard_node;
        standard_node = standard_node->p_next;
        ++index_1;
    }


    for (int i = 0; i < get_total_node_count()-1; ++i) {
        USERDATA * fixed_node = name_list[i];

        for (int j = i+1; j < get_total_node_count(); ++j) {
            if (strcmp(name_list[i]->name, name_list[j]->name) > 0) {
                USERDATA *temp = name_list[i];
                name_list[i] = name_list[j];
                name_list[j] = temp;
            }
        }

    }

    return name_list;


}

void node_data_switch (USERDATA * data_1, USERDATA * data_2) {
    data_1->age = data_2->age;
    strcpy(data_1->name, data_2->name);
    strcpy(data_1->phone, data_2->phone);
}

// 이걸 개 망상함
void swap_node (USERDATA * user_1, USERDATA * user_2) {
    USERDATA temp = * user_1;
    node_data_switch(user_1, user_2);
    node_data_switch(user_2, &temp);
}

// user_1에 user_2를 넣을 떄 user_1의 주소에 존재하는 데이터를 변경합니다.
// 그래서 temp가 user_1의 주소를 가지고 있으면 node_data_switch에 의해서 변경된 값의 주소를 가리킵니다.
// 그래서 변경해봤자 의미없어집니다. -> 데이터 자체를 들고 있어야 함
// void swap_node (USERDATA * user_1, USERDATA * user_2) {
//     USERDATA &temp = user_1;
//     node_data_switch(user_1, user_2);
//     node_data_switch(user_2, temp);
// }

void sort_list_by_name (void) {
       
    if (is_empty()) {
        return ;
    }

    USERDATA * standard_node = global_head_node.p_next;
    USERDATA * select_node = NULL;
    USERDATA * change_node = NULL;


    while (standard_node != NULL && standard_node != global_tail_node.p_prev) {
        select_node = standard_node;
        change_node = standard_node->p_next;

        while (change_node != NULL && change_node != &global_tail_node) {

            if (strcmp(select_node->name, change_node->name) > 0) {
                select_node = change_node;
            }

            change_node = change_node->p_next;
        }

        if (standard_node != select_node) {
            swap_node(standard_node, select_node);
        }

        select_node = NULL;
        standard_node = standard_node->p_next;

    }

}

void sort_list_by_age (void) {
    
    if (is_empty()) {
        return;
    }

    USERDATA * standard_node = global_head_node.p_next;
    USERDATA * select_node = NULL;
    USERDATA * change_node = NULL;

    while (standard_node != NULL && standard_node != global_tail_node.p_prev) {

        select_node = standard_node;
        change_node = standard_node->p_next;

        while (change_node != NULL && change_node != &global_tail_node) {
            if (select_node->age > change_node->age) {
                select_node = change_node;
            }
            change_node = change_node->p_next;
        }

        if (standard_node != select_node) {
            swap_node(standard_node, select_node);
        }

        select_node = NULL;
        standard_node = standard_node->p_next;

    }


}

int search_list_by_name(USERDATA* user, char* name) {

    USERDATA * standard_node = global_head_node.p_next;

    while (standard_node != &global_tail_node) {
        if (strcmp(standard_node->name, name) == 0) {
            memcpy(user, standard_node, sizeof(USERDATA));
            return 1;
        }
        standard_node = standard_node->p_next;
    }

    return 0;

}

int search_list_by_phone (USERDATA * user, char * phone) {

    USERDATA * standard_node = global_head_node.p_next;

    while (standard_node != &global_tail_node) {

        if (strcmp(standard_node->phone, phone) == 0) {
            memcpy(user, standard_node, sizeof(USERDATA));
            return 1;
        }

        standard_node = standard_node->p_next;
    }

    return 0;

}

int search_list_by_age (int age) {

    USERDATA * standard_node = global_head_node.p_next;

    while (standard_node != &global_tail_node) {

        if (standard_node->age == age) {
            return 1;
        }

        standard_node = standard_node->p_next;
    }

    return 0;
    

}

int remove_by_name(char* name) {

    USERDATA * standard_node = global_head_node.p_next;
    USERDATA * next_node = NULL;
    USERDATA * prev_node = NULL;

    while (standard_node != NULL && standard_node != &global_tail_node) {
        
        if (strcmp(standard_node->name, name) == 0) {

            next_node = standard_node->p_next;
            prev_node = standard_node->p_prev;

            next_node->p_prev = prev_node;
            prev_node->p_next = next_node;

            free(standard_node);
            --g_total_node_count;
            UpdateIndexAll();
            return 1;

        }

         standard_node = standard_node->p_next;

    }

    return 0;

}

void** search_by_age_range(int min, int max, int* count) {
    
}