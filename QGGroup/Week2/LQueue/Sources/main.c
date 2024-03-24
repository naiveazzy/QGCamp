#include <stdio.h>
#include <stdlib.h>
#include "../Headers/LQueue.h"

#define QUEUE_LENGTH 8

char string_menu[13][36] = {
	"Here are all functions you can use:",
	"A.initLQueue",
	"B.DestoryLQueue",
	"C.IsEmptyLQueue",
	"D.GetHeadLQueue",
	"E.LengthLQueue",
	"F.EnLQueue",
	"G.DeLQueue",
	"H.ClearLQueue",
	"I.TraverseLQueue",
	"J.QUIT",
	"Do NOT ask fried rice.",
	"Enter the function you selected:"
};

int main() {

	Node* p_queue;
	char key;

	while (1) {
		system("cls");
		for (int i = 0; i < 13; i++) {
			puts(string_menu[i]);
		}

		scanf_s("%c", &key, sizeof(char));

		switch (key) {
		case 'A':
		{
			p_queue = (LQueue*)malloc(sizeof(LQueue));
			InitLQueue(p_queue);
			printf("Init successed!\n");
			break;
		}

		case 'B':
		{
			DestoryLQueue(p_queue);
			printf("Destory successed!\n");
			break;
		}

		case 'C':
		{
			printf("Is the queue empty?: %s\n", (IsEmptyLQueue(p_queue) ? "Yes" : "No"));
			break;
		}

		case 'D':
		{
			int data;
			if (GetHeadLQueue(p_queue, &data)) {
				printf("The head data of queue is: %d\n", data);
			}
			else {
				printf("Get head data fail, did you init the queue?\n");
			}
			break;
		}

		case 'E':
		{
			int length = LengthLQueue(p_queue);

			printf("The length of queue is %d\n", length);
			break;
		}

		case 'F':
		{
			int data;
			printf("Please enter the data you want to push:");
			scanf_s("%d", &data);
			if (EnLQueue(p_queue, &data)) {
				printf("Push SUCCESS!\n");
			}
			else {
				printf("Push failed, did you init the stack?\n");
			}
			break;
		}

		case 'G':
		{
			if (DeLQueue(p_queue)) {
				printf("Delele SUCCESS!\n");
			}
			else {
				printf("Delete failed, did you init the stack?\n");
			}
			break;
		}

		case 'H':
		{
			ClearLQueue(p_queue);
			printf("Clear success!\n");
			break;
		}

		case 'I':
		{
			void (*func)(void*) = NULL;
			func = LPrint;
			if (!TraverseLQueue(p_queue, func)) {
				printf("Traverse failed, did you init the queue?\n");
			}
			break;
		}

		case 'J':
		{
			return 0;
		}

		default:
		{
			printf("Wrong input, please try again.\n");
			break;
		}
		}

		// 忽略剩下回车前的所有字母
		do {
			scanf_s("%c", &key, sizeof(char));
		} while (key != '\n');

		printf("Press ENTER to continue.");
		scanf_s("%c", &key, sizeof(char));
		fflush(stdin);
	}

	return 0;
}

/*
	初始化队列
	初始后的队列头尾为环链表中的一个元素
	但length为0，即无元素
*/
void InitLQueue(LQueue* Q) {
	if (Q == NULL) return;
	
	Node* pL = (Node*)malloc(sizeof(Node));
	Node* pR = (Node*)malloc(sizeof(Node));

	if (pL == NULL || pR == NULL) return;

	pL->next = pR;

	for (int i = 2; i < QUEUE_LENGTH; i++) {
		pR->next = (Node*)malloc(sizeof(Node));
		if (pR->next == NULL) return;
		pR = pR->next;
	}

	pR->next = pL;

	Q->front = pL;
	Q->rear = pL;
	Q->length = 0;
}

/*
	销毁队列
*/
void DestoryLQueue(LQueue* Q) {
	
	if (Q == NULL) return;

	if (Q->front == NULL || Q->rear == NULL) return;

	Node* p_next = Q->front;
	Node* p;

	while (p_next != Q->rear) {
		p = p_next;
		p_next = p_next->next;
		free(p);
	}

	free(p_next);
}

/*
	判断队列是否为空
*/
Status IsEmptyLQueue(const LQueue* Q) {

	if (Q == NULL) return TRUE;

	if (Q->length == 0) return TRUE;

	if (Q->front == Q->rear) return TRUE;

	return FALSE;
}

/*
	查看队头元素
*/
Status GetHeadLQueue(LQueue* Q, void* e) {

	if (Q == NULL) return FALSE;

	if (Q->length == 0) return FALSE;

	if (Q->front == NULL) return FALSE;

	int* elem = (int*)e;
	int* data = (int*)Q->front->data;

	*elem = *data;

	return TRUE;
}

/*
	确定队列长度
*/
int LengthLQueue(LQueue* Q) {

	if (Q == NULL) return 0;

	if (Q->front == NULL || Q->rear == NULL) return 0;

	return Q->length;
}

/*
	进行入队操作
*/
Status EnLQueue(LQueue* Q, void* data) {
	
	if (Q == NULL) return FALSE;

	if (Q->length == QUEUE_LENGTH) return FALSE;

	if (Q->length == 0) {
		Q->front->data = malloc(sizeof(int));
		int* en_elem = (int*)Q->front->data;
		int* data_elem = (int*)data;
		*en_elem = *data_elem;
		Q->length++;

		return TRUE;
	}
	
	Node* p = Q->front;

	// 在队尾的前一个元素进行添加
	while (p->next != Q->rear) {
		p = p->next;
	}

	int* data_elem = (int*)data;

	p->data = malloc(sizeof(int));

	int* en_elem = (int*)p->data;

	*en_elem = *data_elem;

	Q->rear = p;

	Q->length++;

	return TRUE;
}

/*
	出队操作
	将front元素定位到其前一个元素
	出队不返回数据？？
*/
Status DeLQueue(LQueue* Q) {
	
	if (Q == NULL) return FALSE;

	if (Q->front == NULL) return FALSE;

	if (Q->length == 1) {
		Q->length = 0;
		return TRUE;
	}
	
	Node* p = Q->rear;

	while (p->next != Q->front) {
		p = p->next;
	}

	Q->front = p;
	
	Q->length--;

	return TRUE;
}

void ClearLQueue(LQueue* Q) {

	if (Q == NULL) return;

	if (Q->front == NULL || Q->rear == NULL) return;

	Q->rear = Q->front;

	Q->length = 0;
}

/*
	遍历队列
	对每一个元素进行一次foo操作
*/
Status TraverseLQueue(const LQueue* Q, void (*foo)(void* q)) {
	
	if (Q == NULL) return FALSE;

	if (Q->front == NULL || Q->rear == NULL) return FALSE;

	Node* p = Q->front;
	do {
		foo(p->data);
		p = p->next;
	} while (p != Q->rear);

	return TRUE;
}

void LPrint(void* q) {
	int* elem = (int*)q;

	printf("%d ", *elem);
}

