#include <stdio.h>

struct Todo_list {
	int Start;
	int Run;
	char Todo[10];
	struct Todo_list*link;
};

int main() 
{
	char A[10];

	struct Todo_list *head = malloc(sizeof(struct Todo_list));			//// head 노드 생성 (자료 X)

	struct Todo_list *node = malloc(sizeof(struct Todo_list));			//// 노드 생성

	head->link = node;				//// head와 node 연결
	node->Start = 1;
	node->Run = 1;		//// 노드에 값 저장
	node->link = NULL;
	printf("입력 : ");
	scan_s("%s", A, 10);;						//// 링크값 0

	printf("%d %d %s\n", node -> Start, node -> Run, A);

	system("pause");
	return 0;
}
		
/*
int main() 
{
	int num;
	int Start;
	int Run;
	char Todo[20];
	int Dlt;
	int Srh;
	
	
	while(1){
	printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n");
	printf("                    1. 할 일 입력\n");
	printf("                    2. 할 일 지우기\n");
	printf("                    3. 할 일 검색\n\n\n");

	printf("원하는 작업을 입력하시오.\ : ");
	scanf_s("%d", &num);
	printf("\n\n");

	switch (num)
	{
	case 1:
	{
		printf("                    1. 할 일 입력\n\n");
		printf("시작시간 : ");
		scanf_s("%d", &Start);
		printf("소요시간 : ");
		scanf_s("%d", &Run);
		printf("주제 : ");
		scanf_s("%s", &Todo, 10);
		

		
		printf("\n[%d시부터 %d시간동안 할 일 %s를 입력받았습니다.]\n\n\n", Start, Run, Todo);

		break;
	}
	case 2:
	{
		printf("                    2. 할 일 지우기\n\n");
		printf("삭제할 시간 : ");
		scanf_s("%d", &Dlt);
		if (Dlt == -1) {
			printf("\n[모든 할 일을 삭제했습니다.]\n\n\n");
		}
		else {
			printf("\n[%d시 할 일을 삭제했습니다.]\n\n\n", Dlt);
		}

		break;
	}
	case 3:
	{
		printf("                    3. 할 일 검색\n\n");
		printf("검색할 시간 : ");
		scanf_s("%d", &Srh);
		if (Srh == -1) {
			printf("\n[모든 할 일 내역]\n\n\n");
	}
		else {
			printf("\n[%d시 할 일 내역]\n\n\n", Srh);
		}break;
	}
	}
	}


}*/