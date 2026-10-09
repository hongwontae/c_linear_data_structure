#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "singleList.h"


USERDATA g_HeadNode = { 0, "_DummyHead_" };
USERDATA g_TailNode = { 0, "_DummyTail_" };
static unsigned int g_listCount = 0;

unsigned int GetListCount(void)
{
	return g_listCount;
}

unsigned int RecalcListCount(void)
{
	unsigned int cnt = 0;
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		++cnt;
		pTmp = pTmp->pNext;
	}
	g_listCount = cnt;
	return g_listCount;
}


void InitList(void)
{
	ReleaseList();
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;
}

int IsEmpty(void)
{
	if (g_HeadNode.pNext == &g_TailNode ||
		g_HeadNode.pNext == NULL)
		return 1;

	return 0;
}

void ReleaseList(void)
{
	if (IsEmpty())
		return; 

	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pDelete;
	while (pTmp != &g_TailNode)
	{
		pDelete = pTmp;
		pTmp = pTmp->pNext;

		printf("Delete: %d, %s, %s\n",
			pDelete->age, pDelete->name, pDelete->phone);

		free(pDelete);
	}

	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;
}


void NodeDataCopy(USERDATA* pLeft, USERDATA* pRight)
{
	pLeft->age = pRight->age;
	strcpy(pLeft->name, pRight->name);
	strcpy(pLeft->phone, pRight->phone);
}

void SwapNode(USERDATA* pLeft, USERDATA* pRight)
{
	USERDATA tmp = *pLeft;
	NodeDataCopy(pLeft, pRight);
	NodeDataCopy(pRight, &tmp);
}

void SortListByName(void)
{
	if (IsEmpty())
		return;

	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pSelected = NULL;
	USERDATA* pCmp = NULL;
	while (pTmp != NULL && pTmp != g_TailNode.pPrev)
	{
		pSelected = pTmp;
		pCmp = pTmp->pNext;
		while (pCmp != NULL && pCmp != &g_TailNode)
		{
			if (strcmp(pSelected->name, pCmp->name) > 0)
				pSelected = pCmp;

			pCmp = pCmp->pNext;
		}

		if (pTmp != pSelected)
			SwapNode(pTmp, pSelected);

		pSelected = NULL;
		pTmp = pTmp->pNext;
	}
}

void SortListByAge(void)
{
	// 비어있다면 돌려보냅니다.
	if (IsEmpty())
		return;

	// p_tmp는 실질적인 첫 노드
	// p_selected는 선택정렬의 노드
	// p_cmp는 움직일 노드
	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pSelected = NULL;
	USERDATA* pCmp = NULL;

	// p_tmp가 null이거나 p_tmp가 더미 테일 노드의 뒷 부분이라면 지속을 멈춥니다.
	// p_tmp = p_tmp -> p_next로 모든 노드를 돕니다.
	// 실질적인 마지막 노드를 신경쓰지 않아도 되는 이유는 선택 정렬로 인해서 마지막 노드를 정렬되기 때문입니다.
	while (pTmp != NULL && pTmp != g_TailNode.pPrev)
	{
		// p_selected에 기준 노드를 전달해주고 p_cmp는 그 다음 노드를 전달합니다.
		pSelected = pTmp;
		pCmp = pTmp->pNext;

		// p_cmp가 null이 아니거나 p_cmp가 tailnode가 아니라면 지속합니다.
		while (pCmp != NULL && pCmp != &g_TailNode)
		{
			// 나이를 비교합니다.
			// 나이 비교시 더 높으면 선택정렬의 노드로 위치됩니다.
			if (pSelected->age > pCmp->age)
				pSelected = pCmp;
			// 이를 지속합니다.
			pCmp = pCmp->pNext;
		}

		// 만약 변경이 되지 않았다면 아무것도 하지 않습니다.
		// 변경이 되었다면 SwapNode를 통해 값만 바꿔줍니다.
		if (pTmp != pSelected)
			SwapNode(pTmp, pSelected);
		
		// p_selected를 다시 널로 만들고 선택정렬을 다음 노드로 바꿉니다.
		pSelected = NULL;
		pTmp = pTmp->pNext;
	}
}

// 정수를 반환하는 함수입니다.
// 찾는 이름이 존재하면 1 그렇지 않으면 0을 반환합니다.
// 매개변수로 받은 p_user는 구조체 주소고 이를 memcpy하면 호출자 함수의 p_user가 업데이트 됩니다.
// p_tmp는 실질적인 첫 노드 -> 이를 계속 굴려서 찾으면 memcpy
int SearchListByName(USERDATA* pUser, char* pszName)
{
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (strcmp(pTmp->name, pszName) == 0)
		{
			memcpy(pUser, pTmp, sizeof(USERDATA));
			return 1;
		}

		pTmp = pTmp->pNext;
	}

	return 0;
}

int SearchListByPhone(USERDATA* pUser, char* pszPhone)
{
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (strcmp(pTmp->phone, pszPhone) == 0)
		{
			memcpy(pUser, pTmp, sizeof(USERDATA));
			return 1;
		}

		pTmp = pTmp->pNext;
	}

	return 0;
}

int RemoveByName(char* pszName)
{
	USERDATA* pCur = g_HeadNode.pNext;
	USERDATA* pNextNode;
	USERDATA* pPrevNode;
	while (pCur != NULL && pCur != &g_TailNode)
	{
		if (strcmp(pCur->name, pszName) == 0)
		{
			pNextNode = pCur->pNext;
			pPrevNode = pCur->pPrev;

			pNextNode->pPrev = pCur->pPrev;
			pPrevNode->pNext = pCur->pNext;

			free(pCur);
			--g_listCount;
			return 1;
		}

		pCur = pCur->pNext;
	}

	return 0;
}

void AddNewNode(int age, char* pszName, char* pszPhone)
{
	USERDATA* pNewNode = calloc(1, sizeof(USERDATA));
	pNewNode->age = age;
	strcpy(pNewNode->name, pszName);
	strcpy(pNewNode->phone, pszPhone);

	USERDATA* pPrevNode = g_TailNode.pPrev;
	pPrevNode->pNext = pNewNode;
	pNewNode->pPrev = pPrevNode;
	pNewNode->pNext = &g_TailNode;
	g_TailNode.pPrev = pNewNode;

	++g_listCount;
}

int SearchListByAge(int age)
{
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (pTmp->age == age)
			return 1;

		pTmp = pTmp->pNext;
	}

	return 0;
}


USERDATA ** SearchByAgeRange(int min, int max, int* pCount)
{

	// 일단 자료구조가 정렬된 상태입니다.

	*pCount = 0;
	USERDATA* pMin = NULL;
	USERDATA* pMax = NULL;
	USERDATA* pTmp = g_HeadNode.pNext;

	// p_tmp는 첫 노드부터 시작합니다.
	while (pTmp != &g_TailNode)
	{
		// 정렬된 자료구조에서 min보다 같거나 큰 숫자중에 가장 작은 숫자를 구합니다.
		if (pTmp->age >= min)
		{
			pMin = pTmp;
			break;
		}
		pTmp = pTmp->pNext;
	}

	// 만약 min이 널이 아니라면 p_tmp는 p_min의 다음 요소
	if (pMin != NULL)
		pTmp = pMin->pNext;
	else
		// p_min이 널이라면 첫 노드
		pTmp = g_HeadNode.pNext;
	
	// 더미 테일 노드를 만날떄까지 지속합니다.
	while (pTmp != &g_TailNode)
	{
		// p_min이 넘는 노드에서 max보다 작거나 같다면 p_max에 대입합니다.
		// 만약 p_tmp->age가 max를 넘는다면 break로 빠져나옵니다. -> 그 전 노드가 max 노드라서
		if (pTmp->age <= max)
			pMax = pTmp;
		else if (pTmp->age > max)
			break;

		pTmp = pTmp->pNext;
	}

	// 둘 다 null이 아니라면 
	if (pMin != NULL && pMax != NULL)
	{
		// p_tmp는 최소 나이를 가진 p_min 노드의 주소를 받습니다.
		USERDATA* pTmp = pMin;

		// 범위 노드를 세는 로직입니다. -> 컬렉션을 만들기 위해서 필요
		int cnt = 1;
		// p_tmp가 p_max를 만나면 시마이
		while (pTmp != pMax)
		{
			++cnt;
			pTmp = pTmp->pNext;
		}

		// 컬렉션의 개수는 호출자 함수도 알아야 하기 떄문에 역참조 연산자로 업데이트 합니다.
		*pCount = cnt;
		
		// heap 영역에 USERDATA 주소를 담을 수 있는 공간을 cnt만큼 만들고 첫 주소를 반환합니다.
		// 이제 나란히 배치되었기에 인덱스 연산 가능 -> [i]는 값의 타입만큼 이동 -> 값 타입은? USERDATA *
		// 만약 USERDATA * p_node = malloc(sizeof(USERDATA) * cnt)라면? -> 값 자체를 만들어서 보내줘야 함
		// 그렇기에 값에 * USERDATA가 들어가길 원하기에 이중 포인터로 선언합니다.
		USERDATA ** pNodePtrList = malloc(sizeof(USERDATA*) * cnt);

		// p_tmp를 다시 최소 나이를 가진 노드로 변경
		// 컬렉션에 주소를 다시 넣어야 하는 작업을 하려고
		// 이제 최소 ~ 최대에 해당하는 노드의 주소값을 넣습니다.
		pTmp = pMin;
		int i = 0;
		for (; pTmp != pMax; ++i)
		{
			pNodePtrList[i] = pTmp;
			pTmp = pTmp->pNext;
		}
		pNodePtrList[i] = pMax;

		//
		return pNodePtrList;
	}

	return NULL;
}

USERDATA** MakeIndexAge(int* pCnt)
{
	*pCnt = 0;
	
	/// 비어있는지 확인
	if (IsEmpty())
		return NULL;

	USERDATA ** aList;

	// getlistcount()를 호출하면 총 연결 리스트 노드 개수를 알 수 있습니다.
	// alist는 연결 리스트 노드 개수만큼 heap 영역에 USERDATA의 주소를 담을 수 있는 공간을 만듭니다.
	// 즉, alist의 각 요소의 값들은 USERDATA의 주소입니다.
	aList = malloc(sizeof(USERDATA*) * GetListCount());
	// memset으로 만든 공간을 0으로 초기화합니다.
	memset(aList, 0, sizeof(USERDATA*) * GetListCount());
	// pcnt는 연결 리스트 총 개수
	*pCnt = GetListCount();

	// p_tmp는 실질적인 첫 노드
	USERDATA* pTmp = g_HeadNode.pNext;

	// p_tmp가 더미 tail 노드가 아닐 때까지 지속해라
	// 해당 작업 완료 후 aList에는 기존의 연결 리스트 자료구조의 전체 주소가 들어갑니다.
	// 다른 연결 리스트에 주소만 다르게 박는 형태
	for (int i = 0; pTmp != &g_TailNode; ++i)
	{
		aList[i] = pTmp;
		pTmp = pTmp->pNext;
	}

	// 그리고 전체를 돌립니다. -> 마지막 노드는 흐름상 정렬이 될 거라 횟수를 한 번 줄여도 됩니다. -> 선택정렬 알고리즘에 의해서
	// GetlistCount()가 10개라고 가정하고 노드도 10개라고 가정
	for (int i = 0; i < GetListCount() - 1; ++i)
	{
		// j는 항상 기준 노드보다 바로 앞에 존재하는 노드
		// j는 10보다 작아야 함 -> 0 ~ 9 -> 이 때는 모든 노드를 고려해야 함 -> 실제 비교하는 것입니다.
		for (int j = i + 1; j < GetListCount(); ++j)
		{
			// 기준 노드의 나이가 비교 노드의 나이보다 더 크면 주소의 위치를 바꿉니다.
			if (aList[i]->age > aList[j]->age)
			{
				USERDATA* pTmp = aList[i];
				aList[i] = aList[j];
				aList[j] = pTmp;
			}
		}
	}

	// 그리고 정렬된 또 다른 자료구조를 반환합니다.
	// 즉, 기존의 자료구조의 개수를 구한 후, 동적할당을 통해 총 개수에 맞는 USERDATA * 를 가진 자료구조를 만듭니다.
	// 그리고 기존 자료구조의 주소를 그대로 복사합니다.
	// 그리고 나이를 비교해서 주소만 옮깁니다.
	// 이제 자료구조는 두 개입니다. 그러나 하나는 진짜 데이터가 존재하는 자료구조 / 또 하나는 주소로 이루어져 있지만 정렬된 자료구조
	// return 하는 것은 나이로 정렬된 USERDATA *를 값으로 갖는 자료구조입니다.
	return aList;
}

// min과 max는 scanf로 받은 값
USERDATA ** SearchByIndexAgeRange(int min, int max, unsigned int* pCount)
{
	*pCount = 0;
	int cntTotal = 0;
	// 나이를 기준으로 정렬된 USERDATA *를 값으로 갖는 자료구조 -> 배열
	// 여기서는 min/max 고려안한 정렬만 된 새로운 공간을 가진 이중 연결리스트 주소 자료
	USERDATA ** aList = MakeIndexAge(&cntTotal);

	// cntTotal은 기준 노드의 총 개수
	int idxMin = -1, idxMax = 0;
	unsigned int i = 0;
	// 0부터 cntTotal까지 돌림
	// 정렬되고 복사된 자료구조를 토대로 루프를 돕니다.
	// 그러면 첫 번쨰 결과에 걸리는 순간 break로 나와도 됩니다.
	for (i = 0; i < cntTotal; ++i)
	{
		if (aList[i]->age >= min && aList[i]->age <= max)
		{
			idxMin = i;
			idxMax = i;
			break;
		}
	}
	// 최소 나이를 가진 노드의 인덱스가 0과 같거나 0보다 크다면 (3)
	// idxMin = -1인 이유가 if문 false 때문이네
	if (idxMin >= 0)
	{
		// alist[i]->age가 max보다 크다면 그 인덱스를 반환합니다.
		for (; i < cntTotal; ++i)
		{
			if (aList[i]->age <= max)
				idxMax = i;
			else if (aList[i]->age > max)
				break;
		}

		// 최소값 인덱스와 최대값 인덱스를 구했습니다.
		// 실제 그림 그려보니까 +1 맞음 -> 즉, 범위에 위치하는 노드의 개수를 구함
		int length = idxMax - idxMin + 1;

		// 범위에 해당되는 노드 수만큼 동적할당
		USERDATA ** aSelected = malloc(sizeof(USERDATA*) * length);
		// 첫 번쨰 인자는 복사해서 넣을 곳 (저장될 첫 주소)
		// 두 번쨰 인자는 복사를 시작할 위치 (복사을 당해줄 첫 주소)
		// 세 번쨰 인자는 얼마큼 복사를 할 것인지
		// alist는 복사하고 정렬된 userdata *를 값으로 가지고 있는 것 -> 주소 연산은 값의 타입만큼 이동
		memcpy(aSelected, aList + idxMin, sizeof(USERDATA*) * length);

		// 기존에 정렬된 전체는 free
		free(aList);
		aList = NULL;

		// p_count는 범위에 해당되는 길이
		*pCount = length;
		return aSelected;
	}

	free(aList);
	return NULL;
}