#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "singleList.h"

MYNODE g_HeadNode = { 0 };
MYNODE g_TailNode = { 0 };
static unsigned int g_listCount = 0;

// 해석 완료!
// 헤드, 테일 연결, list_count = 0 
void InitList(void)
{
	ReleaseList();
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;
}

// 해석 완료!
// 첫 노드가 테일 노드와 같거나 첫 노드가 NULL이라면 return 1
int IsEmpty(void)
{
	if (g_HeadNode.pNext == &g_TailNode ||
		g_HeadNode.pNext == NULL)
		return 1;

	return 0;
}

// 해석 완료!
// 연결 리스트 구조가 분리되었습니다. -> data와 연결 자료 둘 다 free 해야 합니다.
// 이 떄 p_delete는 연결 자료이고 p_delete->p_data는 data입니다.
// g_listCount를 0으로 만들고 헤드 노드와 테일 노드를 결합합니다.
void ReleaseList(void)
{
	if (IsEmpty())
		return; 

	MYNODE* pTmp = g_HeadNode.pNext;
	MYNODE* pDelete;
	while (pTmp != &g_TailNode)
	{
		pDelete = pTmp;
		pTmp = pTmp->pNext;
		free(pDelete->pData);
		free(pDelete);
	}

	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;
}

// 해석 완료!
// 매개변수로 USERDATA 포인터를 받습니다.
// 포인터->name / 포인터->phone.. key로 생각하는 것을 반환합니다.
// 함수 포인터가 될 예정입니다.
char* GetKey(void* thisPointer)
{
	USERDATA* pUser = (USERDATA*)thisPointer;
	return pUser->name;
	//return pUser->phone;
}

// 해석 완료!
// 노드를 추가하는 함수입니다. 이 때 USERDATA + MYNODE를 만들고 연결해야 합니다.
void AddNewNode(int age, char* pszName, char* pszPhone)
{
	USERDATA* pNewData = calloc(1, sizeof(USERDATA));
	pNewData->age = age;
	strcpy_s(pNewData->name, sizeof(pNewData->name), pszName);
	strcpy_s(pNewData->phone, sizeof(pNewData->phone), pszPhone);

	MYNODE* pNewNode = calloc(1, sizeof(MYNODE));
	pNewNode->pData = pNewData;
	pNewNode->GetKey = GetKey;

	MYNODE* pPrevNode = g_TailNode.pPrev;
	pPrevNode->pNext = pNewNode;
	pNewNode->pPrev = pPrevNode;
	pNewNode->pNext = &g_TailNode;
	g_TailNode.pPrev = pNewNode;

	++g_listCount;
}

// 해석 완료!
// 자료 구조를 받아서 자료 구조의 데이터만 변환하는 코드입니다.
void SwapNode(MYNODE* pLeft, MYNODE* pRight)
{
	void* pTmp = pLeft->pData;
	pLeft->pData = pRight->pData;
	pRight->pData = pTmp;
}

// 해석완료!
// 선택정렬 로직입니다.
// 자료구조에서 GETKEY를 호출해서 인자로 구조에 연결된 자료를 넘겨줍니다.
// 이를 통해 나온 값을 판별합니다.
void SortListByAge(void)
{
	if (IsEmpty())
		return;

	MYNODE* pTmp = g_HeadNode.pNext;
	MYNODE* pSelected = NULL;
	MYNODE* pCmp = NULL;
	while (pTmp != NULL && pTmp != g_TailNode.pPrev)
	{
		pSelected = pTmp;
		pCmp = pTmp->pNext;
		while (pCmp != NULL && pCmp != &g_TailNode)
		{
			if (strcmp(
					pSelected->GetKey(pSelected->pData),
					pCmp->GetKey(pCmp->pData)) > 0)
				pSelected = pCmp;

			pCmp = pCmp->pNext;
		}

		if (pTmp != pSelected)
			SwapNode(pTmp, pSelected);

		pSelected = NULL;
		pTmp = pTmp->pNext;
	}
}