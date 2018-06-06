#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)


typedef struct Node {		////////// 트리 노드 구조 생성 //////////
	int key;
	struct Node *right;
	struct Node *left;
}Node;

void insert_node(Node**proot, Node*new) {		////////// 노드 삽입 함수 //////////
	Node*p = NULL;
	Node*q = NULL;
	p = *proot;		// 탐색할 포인터

	if (*proot == NULL) // 데이터를 처음 받는 경우
	{
		new->right = NULL;
		new->left = NULL;
		*proot = new;
	}
	else {				// 데이터가 이미 입력된 경우
		while (p != NULL) {		// 위치 판별
			if (new->key > p->key) {
				q = p;
				p = p->right;
			}
			else {
				q = p;
				p = p->left;
			}
		}

		// 위치 판별 후 크기를 비교하여 제 위치에 삽입.
		if (new->key > q->key) {
			new->right = NULL;
			new->left = NULL;
			q->right = new;
		}
		else {
			new->right = NULL;
			new->left = NULL;
			q->left = new;
		}
	}
}

void delete_node(Node**proot, int num) {		////////// 노드 삭제 함수 //////////
	Node*p = NULL;
	Node*q = NULL;
	Node*r = NULL;
	p = *proot;		// 탐색할 포인터


	while (p->key != num) {		// 위치 탐색
		if (num > p->key) {
			q = p;
			p = p->right;
		}
		else {
			q = p;
			p = p->left;
		}
	}		// 탐색 후엔 p에 삭제할 노드, q에 삭제하기 전 노드


	if (p->right==NULL && p->left == NULL) {	// 자식 노드가 없는 경우
		if (q->right->key == num)
		{
			q->right = NULL;
		}
		else {
			q->left = NULL;
		}
	}
	else if (p->right == NULL && p->left != NULL) {	// Left만 존재할 경우
		r = p;
		q = p;
		p = p->left;
		while (p->right != NULL) {
			r = p;
			p = p->right;
		}
		q->key = p->key;
		if (p->left == NULL) {
			r->right = NULL;
		}
		else
		{
			r->right = p->left;
		}
	}
	else {		// Right이 있는경우 Right노드만 고려
		r = p;
		q = p;
		p = p->right;
		while (p->left != NULL) {
			r = p;
			p = p->left;
		}
		q->key = p->key;
		if (p->right == NULL) {
			r->left = NULL;
		}
		else
		{
			r->left = p->right;
		}
	}
}

void display_endnode(Node *root)
{
	if (root != NULL)
	{
		display_endnode(root->left);
		if (root->left == NULL && root->right == NULL) {
			printf("%d ", root->key);
		}
		display_endnode(root->right);
	}
}

int num(Node *root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;
	else
		return num(root->left) + num(root->right);
}



typedef struct{
	int heap[200];
	int heap_size;
}HeapType;

init(HeapType*h) {
	h->heap_size = 0;
}

void insert_max_heap(HeapType*HPT, int num) {
	int i;
	i = ++(HPT->heap_size);

	while ((i != 1) && (num < HPT->heap[(i+1)/3])) {
		HPT->heap[i] = HPT->heap[(i+1)/3];
		i = (i+1)/3;
	}
	HPT->heap[i] = num; //삽입
}

int delete_max_heap(HeapType*HPT) {
	int parent, child, out, temp;

	out = HPT->heap[1];
	temp = HPT->heap[(HPT->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= HPT->heap_size) {
		if ((child < HPT->heap_size)) {
			if (HPT->heap[child] > HPT->heap[child + 1] && HPT->heap[child + 1] < HPT->heap[child + 2])  // 세 자식 중 제일 작은놈으로 child 이동
				child++;
			else if (HPT->heap[child] > HPT->heap[child + 2] && HPT->heap[child] > HPT->heap[child + 2])
				child = child + 2;
		}
		if (temp <= HPT->heap[child])  break;	// 정렬이 완료되면 루프문 종료

		HPT->heap[parent] = HPT->heap[child];	// 아래 줄로 이동
		parent = child;
		child  = 3*child - 1;
	}

	HPT->heap[parent] = temp;
	return out; // 젤 첨에 있던 숫자 출력
}



int main()		////////////////////////////// 메인 함수 //////////////////////////////
{
	int i;
	int A[15] = {10, 15, 8, 18, 7, 1, 5, 9, 17, 11, 12, 30, 25, 6, 32};
	HeapType HPT;
	Node *new = NULL;		// 노드 포인터
	Node *proot = NULL;		// root 포인터

	
	printf("                      1. Tree 만들기 \n\n");
	
	for (i = 0; i < 15; i++) {
		new = (Node*)malloc(sizeof(Node));		// 새 노드 포인터 생성
		new->key = A[i];						// 새 노드 포인터 생성
		insert_node(&proot, new);				// 지정된 위치에 삽입
	}

	delete_node(&proot, 9);		// 삭제
	delete_node(&proot, 7);
	delete_node(&proot, 10);


	// 단말노드 출력
	printf("단말 노드 : ");
	display_endnode(proot);
	printf("\n");

	// 노드 개수 출력
	printf("단말노드의 개수 : %d개", num(proot));
	printf("\n\n\n");
	


	printf("                      2. 힙 정렬 하기\n\n");
	printf("오름차순 정리 : ");

	init(&HPT);		// 초기화

	for (i = 0; i < 15; i++) {
		insert_max_heap(&HPT, A[i]);	// 노드 삽입
	}

	for (i = 0; i < 15; i++) {		// 한 개씩 삭제하며 출력
		printf("%d ", delete_max_heap(&HPT));
	}
	

	system("PAUSE");
	return 0;
}

