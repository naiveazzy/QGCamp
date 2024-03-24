/*
	�������ʹ�ڵ��ܹ��洢��������
*/


#include <stdio.h>
#include <stdlib.h>
#include "../Headers/LinkStack.h"

char string_menu[12][36] = {
	"Here are all functions you can use:",
	"A.initLStack",
	"B.isEmptyLStack",
	"C.getTopLStack",
	"D.clearLStack",
	"E.destroyLStack",
	"F.LStackLength",
	"G.pushLStack",
	"H.popLStack",
	"I.quit",
	"Do NOT ask fried rice.",
	"Enter the function you selected:"
};

int main() {
	LinkStack *p_stack = NULL;
	char key;

	while (1) {
		system("cls");
		for (int i = 0; i < 12; i++) {
			puts(string_menu[i]);
		}

		scanf_s("%c", &key, sizeof(char));

		switch (key) {
			case 'A':
			{
				p_stack = (LinkStack*)malloc(sizeof(LinkStack));
				if (initLStack(p_stack)) {
					printf("Init successed!\n");
				}
				else {
					printf("Init Failed!\n");
					return 0;
				}
				break;
			}

			case 'B':
			{
				int isempty = isEmptyLStack(p_stack);
				printf("Is the LinkStack empty?: %s\n", (isempty ? "Yes" : "No"));
				break;
			}

			case 'C':
			{
				ElemType e;
				if (getTopLStack(p_stack, &e)) {
					printf("The top elem of stack is %d\n", e);
				} else {
					printf("Get top elem ERROR, did you init the stack?\n");
				}
				break;
			}

			case 'D':
			{
				if (clearLStack(p_stack)) {
					printf("Clear stack SUCCESS!\n");
				} else {
					printf("Clear failed, did you init the stack?\n");
				}
				break;
			}

			case 'E':
			{
				if (destroyLStack(p_stack)) {
					printf("Destroy SUCCESS!\n");
					free(p_stack);
					p_stack = NULL;
				} else {
					printf("Destroy failed, did you init the stack?\n");
				}
				break;
			}

			case 'F':
			{
				int length;
				if (LStackLength(p_stack, &length)) {
					printf("The length of stack is %d\n", length);
				}
				else {
					printf("Get length of stack failed, did you init the stack?\n");
				}
				break;
			}

			case 'G':
			{
				ElemType data;
				printf("Please enter the data you want to push:");
				scanf_s("%d", &data);
				if (pushLStack(p_stack, data)) {
					printf("Push SUCCESS!\n");
				} else {
					printf("Push failed, did you init the stack?\n");
				}
				break;
			}
				
			case 'H':
			{
				ElemType data;
				if (popLStack(p_stack, &data)) {
					printf("The pop of elem is %d\n", data);
				} else {
					printf("Pop failed, did you init the stack? Do elems exist?\n");
				}
				break;
			}

			case 'I':
			{
				return 0;
			}

			default:
			{
				printf("Wrong input, please try again.\n");
				break;
			}
		}

		// ����ʣ�»س�ǰ��������ĸ
		do {
			scanf_s("%c", &key, sizeof(char));
		} while (key != '\n');

		printf("Press ENTER to continue.");
		scanf_s("%c", &key, sizeof(char));
		fflush(stdin);
	}

	return 0;
}

// ��ʼ��ջ����ջ��Ԫ��
// ��ʼ���󳤶�Ϊ0
Status initLStack(LinkStack* s) {

	if (s == NULL) return ERROR;

	s->count = 0;
	s->top = NULL;
	
	return SUCCESS;
}

// ���ջ�Ƿ�Ϊ��
Status isEmptyLStack(LinkStack* s) {

	// ���ջָ�롢ջ��Ԫ��ָ��Ϊ�գ�������
	if (s == NULL) return SUCCESS;
	if (s->top == NULL) return SUCCESS;

	// ���ջԪ������Ϊ0 ������
	if (s->count == 0) return SUCCESS;

	// ���򷵻ط�
	return ERROR;
}

// ����ջ��Ԫ��
Status getTopLStack(LinkStack* s, ElemType* e) {

	// ���ջָ��򷵻�Ԫ��ָ��Ϊ�գ����ش���
	if (s == NULL || e == NULL) return ERROR;

	// ���ջԪ������Ϊ0��ջ��Ԫ��Ϊ�գ����ش���
	if (s->count == 0 || s->top == NULL) return ERROR;

	// ����ջ��Ԫ��
	*e = s->top->data;

	return SUCCESS;
}

// ���ջ
// ��ջ����Ԫ�ص�ֵ��գ�������ռ�
// ʹcount = 0
Status clearLStack(LinkStack* s) {
	
	if (s == NULL) return ERROR;

	s->count = 0;

	StackNode* p = s->top;

	//����Ԫ��ֵ��գ������ɲ���
	while (p != NULL) {
		p->data = 0;
		p = p->next;
	}

	return SUCCESS;
}

// ����ջ
// ��ջ������Ԫ���ͷ�
Status destroyLStack(LinkStack* s) {
	
	if (s == NULL) return ERROR;

	s->count = 0;

	StackNode* p = s->top;
	StackNode* p_cache;

	//��ջ������Ԫ���ͷ�
	//pΪ��һԪ�أ�p_cacheΪ��ǰԪ��
	while (p->next != NULL) {
		p_cache = p;
		p = p->next;
		free(p_cache);
	}

	return SUCCESS;
}

/*
	����ջ����
	����ջ��Ԫ��
*/
Status LStackLength(LinkStack* s, int* length) {
	
	if (s == NULL) return ERROR;

	StackNode* p = s->top;
	*length = 0;

	//����Ԫ�أ�����length
	while (p != NULL) {
		(*length)++;
		p = p->next;
	}

	return SUCCESS;
}

/*
	��ջ
	�����¿ռ�����ջ��
*/
Status pushLStack(LinkStack* s, ElemType data) {

	if (s == NULL) return ERROR;

	int length;
	LStackLength(s, &length);

	if (s->count < length) {

		StackNode* p = s->top;
		for (int i = 1; i < (length - s->count); i++) {
			p = p->next;
		}

		p->data = data;

	} else {

		// �����¿ռ�
		StackNode* newnode = (StackNode*)malloc(sizeof(StackNode));

		if (newnode == NULL) return ERROR;

		s->count++;

		//����Ԫ������ջ��
		newnode->data = data;
		newnode->next = s->top;
		s->top = newnode;

		return SUCCESS;
	}
	
}

/*
	��ջ
	�ͷ�ջ��Ԫ�ز�����Ԫ��ֵ
*/
Status popLStack(LinkStack* s, ElemType* data) {

	if (s == NULL) return ERROR;

	if (s->count == 0 || s->top == NULL) return ERROR;

	StackNode* p = s->top;

	//��Ԫ�ص���
	s->top = p->next;
	*data = p->data;
	s->count--;
	free(p);

	return SUCCESS;
}
