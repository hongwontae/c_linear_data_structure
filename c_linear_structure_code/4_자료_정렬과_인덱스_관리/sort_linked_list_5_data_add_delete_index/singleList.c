#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "singleList.h"


USERDATA g_HeadNode = { 0, "_DummyHead_" };
USERDATA g_TailNode = { 0, "_DummyTail_" };
static unsigned int g_listCount = 0;

USERDATA** g_idxListAge = NULL;
USERDATA** g_idxListName = NULL;

// 해석완료! 총 노드 개수
unsigned int GetListCount(void)
{
	return g_listCount;
}

// 해석 완료!
// 기존 연결 리스트 개수를 다시 세는 함수
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

// 해석완료!
void InitList(void)
{
	// 초기화하고 더미 헤드-테일을 연결하고 총 노드개수 = 0 / 각 인덱스을 NULL로 초기화
	ReleaseList();
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;

	g_idxListAge = NULL;
	g_idxListName = NULL;
}

// 해석완료!
int IsEmpty(void)
{
	// 첫 노드가 더미 테일 노드가 아니고 첫 노드가 NULL이 아니라면 return 1; ! retunr 0
	if (g_HeadNode.pNext == &g_TailNode ||
		g_HeadNode.pNext == NULL)
		return 1;

	return 0;
}

// 해석완료!
void ReleaseList(void)
{
	if (IsEmpty())
		return; 

	// 다 돌면서 연결 리스트를 해제시킵니다.
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

	// 더미 노드들을 연결시키고 총 노드 개수를 0으로 만듭니다.
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;

	// 인덱스들이 NULL이 아니라면 동적할당 해제를 시키고 NULL을 할당합니다.
	if (g_idxListAge != NULL)
	{
		free(g_idxListAge);
		g_idxListAge = NULL;
	}

	if (g_idxListName != NULL)
	{
		free(g_idxListName);
		g_idxListName = NULL;
	}
}

// 해석완료! -> 인덱스 사용으로 지금 안씀
void NodeDataCopy(USERDATA* pLeft, USERDATA* pRight)
{
	pLeft->age = pRight->age;
	strcpy(pLeft->name,  pRight->name);
	strcpy(pLeft->phone, pRight->phone);
}

// 해석완료! -> 인덱스 사용으로 지금 안씀
void SwapNode(USERDATA* pLeft, USERDATA* pRight)
{
	USERDATA tmp = *pLeft;
	NodeDataCopy(pLeft, pRight);
	NodeDataCopy(pRight, &tmp);
}

// sortListBy.. -> 인덱스 사용으로 지금 안씀
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

// 해석완료!
// 전체 리스트를 돌아서 일치하는 이름찾고 return
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

// 해석완료 !
int RemoveByName(char* pszName)
{
	// 첫 노드 p_cur
	USERDATA* pCur = g_HeadNode.pNext;
	USERDATA* pNextNode;
	USERDATA* pPrevNode;
	
	// p_cur이 테일 노드가 아닐때까지 돌립니다.
	while (pCur != NULL && pCur != &g_TailNode)
	{
		// 일치하면 값 지우고 노드 정리하고 리스트 빼고 인덱스 갱신하고 return 1
		if (strcmp(pCur->name, pszName) == 0)
		{
			pNextNode = pCur->pNext;
			pPrevNode = pCur->pPrev;

			pNextNode->pPrev = pCur->pPrev;
			pPrevNode->pNext = pCur->pNext;

			free(pCur);
			--g_listCount;
			UpdateIndexAll();
			return 1;
		}

		pCur = pCur->pNext;
	}

	return 0;
}

// 해석완료!
void AddNewNode(int age, char* pszName, char* pszPhone)
{
	// 1개의 공간을 만들고 그 공간의 크기는 sizeof(userdata)로 하겠다는 의미입니다. 그리고 값을 0 초기화
	USERDATA* pNewNode = calloc(1, sizeof(USERDATA));
	pNewNode->age = age;
	strcpy(pNewNode->name,pszName);
	strcpy(pNewNode->phone, pszPhone);

	// p_next, p_prev를 최신화합니다.
	USERDATA* pPrevNode = g_TailNode.pPrev;
	pPrevNode->pNext = pNewNode;
	pNewNode->pPrev = pPrevNode;
	pNewNode->pNext = &g_TailNode;
	g_TailNode.pPrev = pNewNode;

	// 총 노드 개수 + 1
	++g_listCount;

	// 생성할 때마다 인덱스 갱신
	UpdateIndexAll();
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

// 해석완료!
void** MakeIndexAge(int* pCnt)
{
	*pCnt = 0;

	// 비어 있다면 돌려보냅니다.
	if (IsEmpty())
		return NULL;

	// 인덱스 접근으로 주소를 넣기 위한 선언
	USERDATA** aList;

	// 하나의 공간의 값은 USERDATA * 타입으로 채울것이며, 주소는 USERDATA **이다.
	// 그리고 malloc이 반환하는 것은 주소이다. -> USERDATA **이다.
	// aList가 인덱스 접근시 도달하는 값은 USERDATA *이다. -> 주소를 가지고 컨트롤 가능
	aList = malloc(sizeof(USERDATA*) * GetListCount());

	// 그리고 모든 aList를 0으로 초기화
	memset(aList, 0, sizeof(USERDATA*) * GetListCount());

	// p_cnt는 LIST 개수
	*pCnt = GetListCount();

	// 첫 노드부터 시작 p_tmp; p_tmp가 테일 노드가 될 떄가지 반복합니다.
	// 그리고 aList의 인덱스 접근 값은 기존 연결리스트 주소로 채워집니다.
	USERDATA* pTmp = g_HeadNode.pNext;
	for (int i = 0; pTmp != &g_TailNode; ++i)
	{
		aList[i] = pTmp;
		pTmp = pTmp->pNext;
	}

	// 선택정렬을 통해 나이를 기준으로 한 인덱스 생성 완료
	for (unsigned int i = 0; i < GetListCount() - 1; ++i)
	{
		for (unsigned int j = i + 1; j < GetListCount(); ++j)
		{
			if (aList[i]->age > aList[j]->age)
			{
				USERDATA* pTmp = aList[i];
				aList[i] = aList[j];
				aList[j] = pTmp;
			}
		}
	}

	return aList;
}

// 해석완료!
void** SearchByIndexAgeRange(int min, int max, unsigned int* pCount)
{
	// 일단은 cnt는 0
	*pCount = 0;
	unsigned int cntTotal = 0;
	// make_index_age를 통해 정렬된 인덱스를 가져옵니다.
	USERDATA** aList = (USERDATA**)MakeIndexAge(&cntTotal);

	int idxMin = -1, idxMax = 0;
	unsigned int i = 0;
	// cntTotal -> 기존 연결리스트 노드 개수
	// min이상 max 이하의 값을 가져오는데 정렬되었으니 가장 낮은 min을 가져옵니다.
	for (i = 0; i < cntTotal; ++i)
	{
		if (aList[i]->age >= min && aList[i]->age <= max)
		{
			idxMin = i;
			idxMax = i;
			break;
		}
	}

	// idxMin이 0과 같거나 크면 실행/ 그렇지 않으면 free 후 NULL 반환
	if (idxMin >= 0)
	{
		// 전체 노드 개수만큼 돌림, max 이하라면 계속 갱신, max 넘으면 넘춤
		for (; i < cntTotal; ++i)
		{
			if (aList[i]->age <= max)
				idxMax = i;
			else if (aList[i]->age > max)
				break;
		}

		// 범위에 들어가는 개수 계산
		int length = idxMax - idxMin + 1;
		// 범위에 들어가는 length를 기준으로 동적할당
		USERDATA** aSelected = malloc(sizeof(void*) * length);
		// memcpy는 주소를 받고 주소에 해당되는 값에 데이터를 복사하는로직
		// aSelected와 aList는 주소 -> USERDATA ** / 주소의 값은 USERDATA * -> USERDATA *을 복사해서 갱신
		// idxMin과 length를 통해 최소 ~ 최대만큼 컬렉션 생성
		memcpy(aSelected, aList + idxMin, sizeof(void*) * length);

		// 기존의 인덱스 해제
		free(aList);

		// 컬렉션 개수 업데이트 그리고 반환
		*pCount = length;
		return aSelected;
	}

	free(aList);
	return NULL;
}

// 해석 완료! -> MakeIndexAge와 같은 흐름
void** MakeIndexName(int* pCnt)
{
	*pCnt = 0;
	if (IsEmpty())
		return NULL;

	USERDATA** aList;
	aList = malloc(sizeof(USERDATA*) * GetListCount());
	memset(aList, 0, sizeof(USERDATA*) * GetListCount());
	*pCnt = GetListCount();

	USERDATA* pTmp = g_HeadNode.pNext;
	for (int i = 0; pTmp != &g_TailNode; ++i)
	{
		aList[i] = pTmp;
		pTmp = pTmp->pNext;
	}

	for (unsigned int i = 0; i < GetListCount() - 1; ++i)
	{
		for (unsigned int j = i + 1; j < GetListCount(); ++j)
		{
			if (strcmp(aList[i]->name, aList[j]->name) > 0)
			{
				USERDATA* pTmp = aList[i];
				aList[i] = aList[j];
				aList[j] = pTmp;
			}
		}
	}

	return aList;
}

// 해석완료!
void UpdateIndexAll(void)
{
	// 만약 인덱스가 NULL이 아니라면 초기화하고 NULL을 대입
	if (g_idxListAge != NULL)
	{
		free(g_idxListAge);
		g_idxListAge = NULL;
	}

	if (g_idxListName != NULL)
	{
		free(g_idxListName);
		g_idxListName = NULL;
	}

	int cnt = 0;
	// 인덱스를 생성합니다. 이 떄 cnt의 주소값을 받아갑니다.
	// 반환값은 USERDATA ** 그리고 각 인덱스는 전역 변수입니다.
	g_idxListAge = (USERDATA**)MakeIndexAge(&cnt);
	g_idxListName = (USERDATA**)MakeIndexName(&cnt);
}