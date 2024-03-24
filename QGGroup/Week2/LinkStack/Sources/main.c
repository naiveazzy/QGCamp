/*
	待增加项：使节点能够存储任意数据
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

// 初始化栈，无栈顶元素
// 初始化后长度为0
Status initLStack(LinkStack* s) {

	if (s == NULL) return ERROR;

	s->count = 0;
	s->top = NULL;
	
	return SUCCESS;
}

// 检测栈是否为空
Status isEmptyLStack(LinkStack* s) {

	// 如果栈指针、栈顶元素指针为空，返回是
	if (s == NULL) return SUCCESS;
	if (s->top == NULL) return SUCCESS;

	// 如果栈元素数量为0 返回是
	if (s->count == 0) return SUCCESS;

	// 否则返回否
	return ERROR;
}

// 返回栈顶元素
Status getTopLStack(LinkStack* s, ElemType* e) {

	// 如果栈指针或返回元素指针为空，返回错误
	if (s == NULL || e == NULL) return ERROR;

	// 如果栈元素数量为0或栈顶元素为空，返回错误
	if (s->count == 0 || s->top == NULL) return ERROR;

	// 返回栈顶元素
	*e = s->top->data;

	return SUCCESS;
}

// 清空栈
// 将栈所有元素的值清空，保留其空间
// 使count = 0
Status clearLStack(LinkStack* s) {
	
	if (s == NULL) return ERROR;

	s->count = 0;

	StackNode* p = s->top;

	//将各元素值清空，可做可不做
	while (p != NULL) {
		p->data = 0;
		p = p->next;
	}

	return SUCCESS;
}

// 销毁栈
// 将栈下所有元素释放
Status destroyLStack(LinkStack* s) {
	
	if (s == NULL) return ERROR;

	s->count = 0;

	StackNode* p = s->top;
	StackNode* p_cache;

	//将栈下所有元素释放
	//p为下一元素，p_cache为当前元素
	while (p->next != NULL) {
		p_cache = p;
		p = p->next;
		free(p_cache);
	}

	return SUCCESS;
}

/*
	返回栈长度
	遍历栈各元素
*/
Status LStackLength(LinkStack* s, int* length) {
	
	if (s == NULL) return ERROR;

	StackNode* p = s->top;
	*length = 0;

	//遍历元素，增加length
	while (p != NULL) {
		(*length)++;
		p = p->next;
	}

	return SUCCESS;
}

/*
	入栈
	申请新空间塞入栈中
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

		// 申请新空间
		StackNode* newnode = (StackNode*)malloc(sizeof(StackNode));

		if (newnode == NULL) return ERROR;

		s->count++;

		//将新元素塞入栈中
		newnode->data = data;
		newnode->next = s->top;
		s->top = newnode;

		return SUCCESS;
	}
	
}

/*
	出栈
	释放栈顶元素并返回元素值
*/
Status popLStack(LinkStack* s, ElemType* data) {

	if (s == NULL) return ERROR;

	if (s->count == 0 || s->top == NULL) return ERROR;

	StackNode* p = s->top;

	//将元素弹出
	s->top = p->next;
	*data = p->data;
	s->count--;
	free(p);

	return SUCCESS;
}
