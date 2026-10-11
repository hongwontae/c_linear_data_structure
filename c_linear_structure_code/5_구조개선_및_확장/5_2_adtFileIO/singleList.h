#pragma once
#include <stdbool.h>

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
} USERDATA;

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