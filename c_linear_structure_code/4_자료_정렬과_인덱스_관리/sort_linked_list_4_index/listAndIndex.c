#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "singleList.h"
#include "ui.h"
#include "test.h"

int main(void)
{
	// g_list_count = 0 초기화
	// 더미 노드 결합
	InitList();
	printf("%zu\n", sizeof(USERDATA));

	// 데이터 추가
	InitDummyData();

	EventLoopRun();

	ReleaseList();
	return 0;
}
