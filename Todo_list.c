#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)


typedef struct Todo_list {
	char Todo[50];
	int Start;
	int Run;
	struct Todo_list *link;
}Todo_list;

void insert_node (Todo_list**phead, Todo_list*p, Todo_list*new_node) {
	if (*phead == NULL) // 데이터를 처음 받는 경우
	{
		new_node->link = NULL;
		*phead = new_node;
	}
	else if(p == NULL) //p가 NULL이면 첫번째 노드로 삽입
	{
		new_node->link = *phead;
		*phead = new_node;
	}
	else //p 다음에 삽입
	{
		new_node->link = p->link;
		p->link = new_node;
	}
}

Todo_list*search(Todo_list*head, int *x, int*y) {
	Todo_list*p=NULL;

	p = head;
	if (head == NULL) {		// 데이터가 없는 경우
		return NULL;
	}
	else if (p->Start >= *x && p->Run >= *y) {	// 가장 빠른 일정은 맨 앞으로
		return NULL;
	}
	else{
		while (p->link != NULL) {
			if ((p->Start)*10000+(p->Run) <= (*x)*10000+*y & (*x)*10000+*y <= (p->link->Start)*10000+(p->link->Run)) {
				return p;
				break;
			}
			p = p->link;
		}
		return p;
	}
}

void search2 (Todo_list *head, Todo_list **prev, Todo_list **removed, int x) {
	Todo_list *p1, *p2;
	p1 = head;
	p2 = NULL;
	
	while (p1 != NULL) {
		if (p1->Start == x) {// 탐색성공
			*prev = p2;
			*removed = p1;
			return;
		}
		p2 = p1;
		p1 = p1->link;
	}
	return; // 탐색실패일경우NULL 반환
}

void remove_node(Todo_list**phead, Todo_list*p, Todo_list*removed)
{
	if (p == NULL)					// 지울 노드가 제일 처음 노드일 경우
		*phead = (*phead)->link;
	else {							// 지울 노드가 중간에 끼어있을 경우
	}
		p->link = removed->link;
	free(removed);
}

void display(Todo_list*head) {
	Todo_list*p = head;
	while (p != NULL) {
		printf("	%d	%d	%s\n", p->Start, p->Run, p->Todo);
		p = p->link;
	}
	printf("\n");
}

void display_2(Todo_list*head, int *a) {
	Todo_list*p = head;
	while (p != NULL) {
		if (p->Start == a){
			printf("	%d	%d	%s\n", p->Start, p->Run, p->Todo);
		}
		p = p->link;
	}
	printf("\n");
}
int main()
{
	int num;
	Todo_list *new = NULL;			// 노드 포인터
	Todo_list *phead = NULL;		// head 포인터
	Todo_list *p = NULL;			// 임의의 포인터
	Todo_list *q = NULL;			// 임의의 포인터2
	while (1)
	{
		printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n");
		printf("                      1. 일정 입력\n");
		printf("                      2. 일정 삭제\n");
		printf("                      3. 일정 검섹\n\n");
		printf("원하는 작업을 입력하시오 : ");
		scanf("%d", &num);
		printf("\n\n");

		switch (num)
		{
			case 1: {
				new = (Todo_list*)malloc(sizeof(Todo_list));		// 새 노드 포인터 생성
				printf("                      1. 일정 입력\n\n");
				printf("시작시간 : ");
				scanf("%d", &new->Start);
				printf("소요시간 : ");
				scanf("%d", &new->Run);
				printf("내    용 : ");
				scanf("%s", &new->Todo);
				new->link = NULL;			// 노드에 값 입력하기

				p = search(phead, &new->Start, &new->Run);		// 삽입될 위치 출력
				insert_node(&phead, p, new);		// 값 넣기

				printf("\n%d시부터 %d시간동안 일정 '%s가 입력되었습니다.\n\n\n\n\n", new->Start, new->Run, &new->Todo);
				break;
			}
			case 2: {
				printf("                      2. 일정 삭제\n\n");
				printf("삭제할 시간 : ");
				scanf("%d", &num);
				if (num == -1) {
					phead = NULL;
				}
				else {
					p = NULL;
					q = phead;
					remove_node(&phead, p, new);
				}
				printf("\n\n\n\n");
				break;
			}
			case 3: {
				printf("                      3. 일정 검섹\n\n");
				
				printf("검섹할 시간 : ");
				scanf("%d", &num);
				if (num == -1) {
					printf("\n예정된 모든 일정입니다.\n");
					printf("\n	시작	시간	내용\n");
					display(phead);
				}
				else {
					printf("\n%d시에 예정된 일정입니다.\n", num);
					printf("\n	시작	시간	내용\n");
					display_2(phead, num);
				}
				printf("\n\n\n\n");
				break;
			}
		}
	}

system("PAUSE");
return 0;
}