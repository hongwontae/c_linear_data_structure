#include <stdio.h>
#include <stdlib.h>
#include "singleList.h"
#include "ui.h"


MY_MENU PrintMenu(void)
{
	MY_MENU input = 0;

	printf("[1]New\t[2]Search\t[3]Search age\t[4]Print\t[5]Remove\t[0]Exit\n");
	scanf("%d%*c", &input);
	return input;
}

// 해석완료!
void PrintList(int wait)
{
	// 전체를 보여줍니다.
	USERDATA* pTmp = &g_HeadNode;
	while (pTmp != NULL)
	{
		printf("[%p] %d, %s, %s [%p]\n",
			pTmp,
			pTmp->age, pTmp->name, pTmp->phone,
			pTmp->pNext);
		pTmp = pTmp->pNext;
	}
	putchar('\n');

	if (wait)
		printf("wait?\n");
}

// 해석완료!
void SearchByNameToRemove(void)
{
	// 이름 찾고 노드를 정리하고 free를 하고 g_list--를 하고 int 1 | 0를 반환합니다.
	char name[32] = { 0 };

	printf("name: ");
	scanf("%s", name);

	USERDATA* pPrev = NULL;

	if (RemoveByName(name))
		puts("Complete");
	else
		puts("Not found");

	printf("search by name to remove\n");
}

// 해석 완료!
void SearchByPhone(void)
{
	char phone[32] = { 0 };

	printf("phone: ");
	scanf("%s\n", phone);

	// 찾으면 1 그렇지 않으면 0을 반환합니다.
	// 내부 찾는 로직은 search_by_name과 일치합니다.
	USERDATA user = { 0 };
	if (SearchListByPhone(&user, phone) > 0)
		printf("Found: %d, %s, %s\n",
			user.age, user.name, user.phone);
	else
		puts("Not found");

	printf("phone\n");
}

// 해석 완료!
void SearchByName(void)
{
	char name[32] = { 0 };

	printf("name: ");
	scanf("%s", name);

	// user 구조체를 하나 생성하고 여기에 대입합니다.
	// 찾으면 Found / 못 찾으면 Not Found를 출력합니니다.
	// 찾으면 1을 반환, 못 찾으면 0반환이라 1이면 found, 0이면 not found
	USERDATA user = { 0 };

	if (SearchListByName(&user, name) > 0)
		printf("Found: %d, %s, %s\n",
			user.age, user.name, user.phone);
	else
		puts("Not found");

	printf("search by name\n");
}

// 해석완료!
void AddNewUser(void)
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

	// add_new_node를 호출하면 전역변수인 g_list_count++를 합니다. -> 인덱스를 만들기 위함
	AddNewNode(age, name, phone);
}

// 해석완료!
// 인덱스를 만들지 않고 기존 이중 연결 리스트 자체를 정렬해서 찾습니다.
void SearchByAge(void)
{
	int min = 0, max = 1, cnt = 0;
	printf("MIN MAX age: ");
	scanf("%d%d%*c", &min, &max);

	// 나이가 낮은 순서대로 정렬됩니다.
	SortListByAge();

	// 
	void** pResult = SearchByAgeRange(min, max, &cnt);
	USERDATA* pTmp = NULL;
	for (int i = 0; i < cnt; ++i)
	{
		pTmp = (USERDATA*)pResult[i];
		printf("%d, %s, %s\n", pTmp->age, pTmp->name, pTmp->phone);
	}

	free(pResult);
	printf("\n");
}

// 해석 완료!
// 인덱스를 만들어서 반환합니다.
void SearchByAgeIndex(void)
{
	// 해당 작업으로 min, max 값을 받아와서 초기화합니다.
	int min = 0, max = 1;
	unsigned int cnt = 0;
	printf("[Index search] MIN MAX age: ");
	scanf("%d%d%*c", &min, &max);

	// 즉, 받은 값은 USERDATA 이중 포인터입니다.
	USERDATA ** pResult = (USERDATA**) SearchByIndexAgeRange(min, max, &cnt);

	
	USERDATA* pTmp = NULL;
	// 최소 ~ 최대 노드를 모은 컬렉션을 print합니다.
	// 길이는 cnt로 처리했습니다.
	for (unsigned int i = 0; i < cnt; ++i)
	{
		pTmp = (USERDATA*)pResult[i];
		printf("%d, %s, %s\n", pTmp->age, pTmp->name, pTmp->phone);
	}
	

	free(pResult);
	printf("hello\n");
}

void EventLoopRun(void)
{
	MY_MENU menu = 0;

	while ((menu = PrintMenu()) != 0)
	{
		switch (menu)
		{
		case NEW:
			AddNewUser();
			break;

		case SEARCH:
			SearchByName();
			//SearchByPhone();
			break;

		case SEARCH_RANGE:
			// SearchByAge();
			SearchByAgeIndex();
			break;

		case PRINT:
			PrintList(1);
			break;

		case REMOVE:
			SearchByNameToRemove();
			break;

		default:
			break;
		}
	}
	puts("Bye~!");
}
