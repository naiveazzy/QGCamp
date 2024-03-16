#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int main() {
    LinkedList *p;
    InitList(p);

    return 0;
}

Status InitList(LinkedList *L) {

    // 如果L本身为空指针，返回错误
    if (L == NULL) return ERROR;

    *L = (LNode*)malloc(sizeof(LNode));
    
    // 如果L指向的指针为空（没有申请到内存），返回错误
    if ((*L) == NULL) return ERROR;

    (*L)->data = -1;
    (*L)->next = NULL;

    return SUCCESS;
}
