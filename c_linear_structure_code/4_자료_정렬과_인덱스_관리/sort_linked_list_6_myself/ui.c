#include "ui.h"
#include "double_linked_list.h"
#include <stdio.h>

MY_MENU PrintMenu(void)
{
	MY_MENU input = 0;

	printf("[1]New\t[2]Search\t[3]Search age\t[4]Print\t[5]Remove\t[0]Exit\n");
	scanf("%d%*c", &input);
	return input;
}

void print_list(int wait)
{
	USERDATA* pTmp = &global_head_node;
	while (pTmp != NULL)
	{
		printf("[%p] %d, %s, %s [%p]\n",
			pTmp,
			pTmp->age, pTmp->name, pTmp->phone,
			pTmp->p_next);
		pTmp = pTmp->p_next;
	}
	putchar('\n');

	if (wait)
		printf("printlist\n");
}

void add_new_user(void)
{
	int age = 0;
	char name[32] = { 0 };
	char phone[32] = { 0 };

	printf("age: ");
	scanf("%d%*c", &age);
	printf("name: ");
	scanf("%s", name);
	printf("phone: ");
	scanf("%s", phone);

	add_new_node(age, name, phone);
}

void search_by_name(void)
{
	char name[32] = { 0 };

	printf("name: ");
	scanf("%s", name);

	USERDATA user = { 0 };
	if (search_list_by_name(&user, name) > 0)
		printf("Found: %d, %s, %s\n",
			user.age, user.name, user.phone);
	else
		puts("Not found");

	printf("searchByName\n");
}

void search_by_name_to_remove(void)
{
	char name[32] = { 0 };

	printf("name: ");
	scanf("%s", name);

	if (remove_by_name(name))
		puts("Complete");
	else
		puts("Not found");

	printf("search_by_name_to_remove\n");
}
// 해석완료!
void event_loop_run(void)
{
	MY_MENU menu = 0;
	// 지금 실질적으로 사용하고 있는 함수는 5개
	while ((menu = PrintMenu()) != 0)
	{
		switch (menu)
		{
		case NEW:
			add_new_user(); // 해석완료!
			break;

		case SEARCH:
			sort_list_by_name();
			search_by_name();
			break;

		case SEARCH_RANGE:
			//SearchByAge();
			// SearchByAgeIndex();  // 해석완료!
			break;

		case PRINT:
			// sort_list_by_name();
			// sort_list_by_age();
			print_list(1);
			break;

		case REMOVE:
			search_by_name_to_remove();
			break;

		default:
			break;
		}
	}
	puts("Bye~!");
}