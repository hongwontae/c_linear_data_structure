#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "singleList.h"

MYNODE g_HeadNode = { 0 };
MYNODE g_TailNode = { 0 };
static unsigned int g_listCount = 0;


// 해석 완료!
void InitList(void)
{
	ReleaseList();
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;
}

// 해석완료!
int IsEmpty(void)
{
	if (g_HeadNode.pNext == &g_TailNode ||
		g_HeadNode.pNext == NULL)
		return 1;

	return 0;
}

// 해석완료!
void ReleaseList(void)
{	
	// 비어 있다면 return
	if (IsEmpty())
		return; 

	// p_tmp는 첫 노드
	// p_delete는 삭제할 노드
	MYNODE* pTmp = g_HeadNode.pNext;
	MYNODE* pDelete;
	while (pTmp != &g_TailNode)
	{
		pDelete = pTmp;
		pTmp = pTmp->pNext;

		// 동적할당된 이름을 초기화
		free(pDelete->pszKey);

		// p_data_cache가 존재한다면 그 캐시데이터를 초기화합니다. -> user 자체 구조체
		if(pDelete->pDataCache != NULL)
			free(pDelete->pDataCache);

		// MYNODE를 초기화
		free(pDelete);
	}

	// 더미 연결
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	// 개수 초기화
	g_listCount = 0;
}

char* GetKey(void* thisPointer)
{
	USERDATA* pUser = (USERDATA*)thisPointer;
	return pUser->name;
	//return pUser->phone;
}

// 해석 완료!
// AddNewNode(user.name, &user, sizeof(user), true, 0);
void AddNewNode(const char* pszKey,
	const void *pData, int sizeData,
	bool bNew, unsigned int offset)
{	

	// MYNODE 구조체 할당
	MYNODE* pNewNode = calloc(1, sizeof(MYNODE));

	// 받아온 이름의 길이구하기
	int lenOfKey = (int)strlen(pszKey);

	// 이름을 key로 가지고 있기 위해 동적할당
	pNewNode->pszKey = malloc(lenOfKey + 1);

	// 그 값을 복사해서 넣기
	strcpy(pNewNode->pszKey, pszKey);

	// p_data는 userdata 구조체 주소
	// &userdata가 NULL이 아니고 그 userdata의 크기가 0보다 이상 -> 실제로 존재하는지
	if (pData != NULL && sizeData > 0)
	{
		// p_new_data에 size 만큼 동적할당
		void* pNewData = malloc(sizeData);
		// memcpy를 통해 구조체 생성하기
		memcpy(pNewData, pData, sizeData);

		// p_data_cache -> MYNODE의 속성에 만든 userdata 자체 연결
		pNewNode->pDataCache = pNewData;

		// size 연결
		pNewNode->sizeOfData = sizeData;
	}

	// b_new -> 새로 만들어졌는가 식별자
	pNewNode->bNew = bNew;

	// offset = 0;
	pNewNode->offset = offset;
	
	// 노드 연결 처리
	MYNODE* pPrevNode = g_TailNode.pPrev;
	pPrevNode->pNext = pNewNode;
	pNewNode->pPrev = pPrevNode;
	pNewNode->pNext = &g_TailNode;
	g_TailNode.pPrev = pNewNode;

	// 전체 리스트 개수 증가
	++g_listCount;
}

// 해석 완료!
void* SearchListByName(char* pszKey)
{
	// 첫 노드
	MYNODE* pTmp = g_HeadNode.pNext;

	 // 노드가 더미 테일 노드를 만나면 멈춥니다.
	while (pTmp != &g_TailNode)
	{
		// 키를 기준으로 찾습니다.
		if (strcmp(pTmp->pszKey, pszKey) == 0)
		{
			// 만약 캐시된 데이터가 존재한다면 바로 return p_tmp
			if (pTmp->pDataCache != NULL)
				return pTmp;

			// 캐시된 데이터가 없다면 데이터가 저장된 파일을 rb 모드로 엽니다. -> 바이너리 모드로 읽기 모드
			// 바이너리 모드로 열면 파일에서 저장할 떄 바이트 크기만큼 쓰고 읽기가 편합니다.
			FILE* fp = fopen("listData.dat", "rb");

			// user 초기화
			USERDATA user = { 0 };

			// fseek()는 파일에서 읽거나 쓸 위치를 원하는 곳으로 이동시키는 함수입니다.
			// int fseek(FILE * stream, long offset, int whence);
			// offset은 기준점으로부터 이동할 바이트 수
			// SEEK_SET은 파일의 시작점을 기준으로 이동
			// SEEK_CUR -> 현재 파일 위치 / SEEK_END -> 파일의 끝 위치
			// 만약 offset이 1이라면 두 번쨰 USERDATA가 존재하는 첫 위치로 이동합니다.
			// USERDATA 크기가 24 -> 1 * 24  -> 24는 두 번쨰 구조체가 위치하는 위치
			fseek(fp, pTmp->offset * sizeof(USERDATA), SEEK_SET);


			// fseek()로 찾으면 커서가 그 쪽을 가리킵니다.
			// 이 떄 1이라면 사이즈만큼 읽습니다.
			// 그리고 &user에 저장합니다. 성공하면 1, 그렇지 않으면 0
			if (fread(&user, sizeof(USERDATA), 1, fp) > 0)
			{
				// 초기화 작업을 합니다.
				pTmp->pDataCache = malloc(sizeof(USERDATA));
				memcpy(pTmp->pDataCache, &user, sizeof(USERDATA));
				pTmp->sizeOfData = sizeof(USERDATA);
				// 찾으면 파일을 닫고 그 포인터를 반환합니다.
				fclose(fp);
				return pTmp;
			}
			// 아무것도 못찾으면 닫습니다.
			fclose(fp);
		}

		pTmp = pTmp->pNext;
	}

	return NULL;
}

// 해석 완료!
int LoadListFromFile(void)
{
	ReleaseList();

	// 파일을 열고 파일 객체를 생성합니다.
	FILE* fp = fopen("listData.dat", "rb");
	// 파일객체가 NULL이라면 retur 0;
	if (fp == NULL)
		return 0;

	// USERDATA 초기화
	USERDATA user = { 0 };
	// offset 0
	unsigned int offset = 0;
	
	// fread(읽은 데이터를 저장할 메모리 주소, 읽을 데이터 크기, 읽을 개수, 파일 포인터)
	// size_t fread(void * ptr, size_t size, size_t count, FILE * stream);
	// 읽으면 1, 하나도 읽지 못하면 0을 반환
	while (fread(&user, sizeof(USERDATA), 1, fp) > 0)
	{
		// add_new_node을 할 떄 두 번쨰 인자에 NULL -> 구조체를 만들지 않으려고 구조만 갖추려고
		// 사이즈는 0, 새로만든게 아니기에 false, offset은 0부터 시작
		AddNewNode(user.name, NULL, 0, false, offset);
		// 다시 지역변수 USERDATA user를 초기화
		memset(&user, 0, sizeof(USERDATA));
		// offset을 증가시킵니다.
		++offset;
	}

	// 완료되었다면 close로 닫기
	fclose(fp);
	return 1;
}

// 해석 완료!
int SaveNewDataToFile(void)
{
	// 파일을 열고 null이라면 return
	// ab+ 모드 -> 파일이 없다면 생성, 기존 데이터 유지, 읽기-쓰기, 쓰기 작업은 파일의 끝에 추가
	// 읽기 위치는 처음 파일 끝으로 설정
	// 데이터 3개 위치 -> 3번쨰 뒤에 추가됨
	FILE* fp = fopen("listData.dat", "ab+");
	if (fp == NULL)
		return 0;

	// 첫 노드를 가져옵니다.
	MYNODE* pTmp = g_HeadNode.pNext;

	// 첫 노드가 NULL이 이거나 더미 테일 노드라면 실행하지 않습니다.
	while (pTmp != NULL && pTmp != &g_TailNode)
	{
		// 새롭게 추가된 노드만 추출합니다.
		// 그리고 그 데이터를 씁니다.
		// fwrite(데이터 주소, 데이터 크기, 데이터 개수, 파일_포인터);
		if (pTmp->bNew == true)
			fwrite(pTmp->pDataCache, pTmp->sizeOfData, 1, fp);

		pTmp = pTmp->pNext;
	}

	fclose(fp);
	return 1;
}

// 해석 완료!
int SaveNodeToFile(MYNODE* pNode)
{
	// 캐시데이터가 없거나 노드에 sizeOfData가 없다면 return 0;
	if (pNode->pDataCache == NULL || pNode->sizeOfData == 0)
		return 0;

	// rb+ 모드 -> 파일이 이미 존재할 떄 기존 데이터 유지, 읽기-쓰기 가능, 쓰기 위치는 처음에 파일 시작점
	FILE* fp = fopen("listData.dat", "rb+");
	if (fp == NULL)
		return 0;

	// 파일 위치를 찾습니다. -> SEEK_SET 처음 위치에서부터 offset * userdata 계산 -> 정확한 위치 target
	fseek(fp, pNode->offset * sizeof(USERDATA), SEEK_SET);

	// 파일을 씁니다. 그리고 닫습니다.
	if (fwrite(pNode->pDataCache, sizeof(USERDATA), 1, fp) > 0)
	{
		fclose(fp);
		return 1;
	}

	return 0;
}
