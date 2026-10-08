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
			if (pSelected->age > pCmp->age)
				pSelected = pCmp;

			pCmp = pCmp->pNext;
		}

		if (pTmp != pSelected)
			SwapNode(pTmp, pSelected);

		pSelected = NULL;
		pTmp = pTmp->pNext;
	}
}

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

void** SearchByAgeRange(int min, int max, int* pCount)
{
	*pCount = 0;
	USERDATA* pMin = NULL;
	USERDATA* pMax = NULL;
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (pTmp->age >= min)
		{
			pMin = pTmp;
			break;
		}
		pTmp = pTmp->pNext;
	}

	if (pMin != NULL)
		pTmp = pMin->pNext;
	else
		pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (pTmp->age <= max)
			pMax = pTmp;
		else if (pTmp->age > max)
			break;

		pTmp = pTmp->pNext;
	}

	if (pMin != NULL && pMax != NULL)
	{
		USERDATA* pTmp = pMin;
		int cnt = 1;
		while (pTmp != pMax)
		{
			++cnt;
			pTmp = pTmp->pNext;
		}

		*pCount = cnt;
		void** pNodePtrList = malloc(sizeof(void*) * cnt);

		pTmp = pMin;
		int i = 0;
		for (; pTmp != pMax; ++i)
		{
			pNodePtrList[i] = pTmp;
			pTmp = pTmp->pNext;
		}
		pNodePtrList[i] = pMax;

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
	// meeset으로 만든 공간을 0으로 초기화합니다.
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

	// 그리고 전체를 돌립니다. -> 마지막 노드는 흐름상 정렬이 될 거라 횟수를 한 번 줄여도 됩니다.
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