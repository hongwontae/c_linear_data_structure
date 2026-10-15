#pragma once
#include <stdbool.h>

// 단순히 자료 구조체
typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
} USERDATA;

// bNEW -> 새로 추가된 것이면 1 / 그렇지 않으면 0
// pszKey -> key의 주소
// pDataCache -> 참조되어서 파일에서 가져온 데이터 그 자체의 주소
// sizeOfData -> 데이터의 size
// offset -> 파일에서 데이터의 위치 -> 이를 통해 전체 수정이 아닌 특정 방향만 수정해서 처리가능
typedef struct MYNODE
{
	bool bNew;
	char* pszKey;
	void* pDataCache;
	unsigned int sizeOfData;
	unsigned int offset;

	struct MYNODE* pNext;
	struct MYNODE* pPrev;
} MYNODE;


extern MYNODE g_HeadNode;
extern MYNODE g_TailNode;

void InitList(void);
void ReleaseList(void);
void AddNewNode(const char* pszKey, const void* pData, int sizeData,
	bool bNew, unsigned int offset);
void* SearchListByName(char* pszKey);
void SortListByAge(void);
int LoadListFromFile(void);
int SaveNewDataToFile(void);
int SaveNodeToFile(MYNODE* pNode);