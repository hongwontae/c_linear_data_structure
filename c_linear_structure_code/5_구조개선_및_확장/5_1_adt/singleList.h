#pragma once

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
} USERDATA;

// 함수 포인터를 선언했습니다.
// GetkEY라는 이름으로 포인터를 선언했습니다.
// 해당 포인터에 들어오는 함수는 반환자료형이 char *,매개변수는 void * thisPointer가 들어옵니다.
typedef struct MYNODE
{
	void* pData;
	struct MYNODE* pNext;
	struct MYNODE* pPrev;
	char* (*GetKey)(void* thisPointer);
} MYNODE;


extern MYNODE g_HeadNode;
extern MYNODE g_TailNode;

void InitList(void);
void ReleaseList(void);
void AddNewNode(int age, char* pszName, char* pszPhone);
void SortListByAge(void);