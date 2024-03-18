#include <stdio.h>
#include <stdlib.h>
#include "duLinkedList.h"


// 为WINDOWS或LINUX系统不同定义
#ifdef _WIN32
#define CLEARSCREEN "cls"
#endif
#ifdef __linux__
#define CLEARSCREEN "clear"
#endif

// 界面字符数组
char char_menu[8][50] = {
    "Here are all function you can use to LinkList:",
    "A.InitList_DuL",
    "B.DestroyList_DuL",
    "C.InsertBeforeList_DuL",
    "D.InsertAfterList_DuL",
    "E.DeleteList_DuL",
    "F.TraverseList_DuL(CheckList)",
    "Please choose the function:(A-J)"
};

void printValue(ElemType e);

int main() {
    // 声明指针
    DuLinkedList *p = (DuLinkedList*)malloc(sizeof(DuLinkedList));
    DuLNode* n;
    ElemType *cache = (ElemType*)malloc(sizeof(ElemType));
    void (*visit)(ElemType) = printValue;

    char ch;

    while(1) {

        // 打印界面
        for (int i = 0; i < 8; i++) {
            puts(char_menu[i]);
        }

        // 排除回车
        do {
            ch = getchar();
        } while (ch == '\n');

        switch(ch) {
            case 'A': 
                if (!InitList_DuL(p)) {
                    printf("The creation has failed!\n");
                } else {
                    printf("The creation is successed.\n");
                }
                break;
            case 'B': 
                DestroyList_DuL(p); 
                printf("The Destroy is completed.\n");
                break;
            case 'C': 
                n = (DuLNode*)malloc(sizeof(DuLNode));
                printf("Please enter the data of the new node:");
                scanf("%d", &n->data);
                n->next = NULL;
                n->prior = NULL;
                InsertBeforeList_DuL(*p, n); break;
            case 'D': 
                n = (DuLNode*)malloc(sizeof(DuLNode));
                printf("Please enter the data of the new node:");
                scanf("%d", &n->data);
                n->next = NULL;
                n->prior = NULL;
                InsertAfterList_DuL(*p, n); break;
            case 'E': 
                DeleteList_DuL(*p, cache);
                printf("Deleted the node after head node, its data is %d", *cache);
                break;
            case 'F': 
                printf("The LinkList:");
                TraverseList_DuL(*p, printValue);
                break;

            default: printf("%c:no opinion!\n", ch); break;
        }

        // 不接收回车，同时保留输出结果
        getchar();
        getchar();
        system(CLEARSCREEN);
    }
    return 0;
}

/* 打印节点值 */
void printValue(ElemType e) {
    printf("%d ", e);
}

/* 初始化链表指针 */
Status InitList_DuL(DuLinkedList *L) {

    // 如果L本身为空指针，返回错误
    if (L == NULL) return ERROR;

    *L = (DuLNode*)malloc(sizeof(DuLNode));

    // 如果L指向的指针为空（没有申请到内存），返回错误
    if ((*L) == NULL) return ERROR;

    (*L)->data = -1;
    (*L)->next = NULL;
    (*L)->prior = NULL;

    return SUCCESS;
}

/* 删除链表指针 */
void DestroyList_DuL(DuLinkedList *L) {

    DuLNode *p = (*L)->next;

    // 循环将p的上一个节点删除并前往下一节点
    while (p->next != NULL) {
        p = p->next;
        free(p->prior);
    }

    // 释放最后一个节点
    free(p);

    // 如果链表反方向有节点
    if ((*L)->prior != NULL) {
        p = (*L)->prior;

        // 沿反方向删除所有节点
        while (p->prior != NULL) {
            p = p->prior;
            free(p->next);
        }
    }

    // 释放p指针的节点
    free(p);

}

/* 将节点q插入到节点p前 */
Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {

    // 如果p节点本身为空，返回错误
    if (p == NULL) return ERROR;

    // n节点为p的前一个节点
    DuLNode *n = p->prior;

    // 修改q的前后节点
    q->next = p;
    q->prior = n;

    // 将q节点放置于节点n和p之间
    p->prior = q;
    if (n != NULL) n->next = q;

    return SUCCESS;
}

/* 将节点q插入到节点p后 */
Status InsertAfterList_DuL(DuLNode *p, DuLNode *q) {

    // 如果p节点本身为空，返回错误
    if (p == NULL) return ERROR;

    // n节点为p的下一个节点
    DuLNode *n = p->next;

    // 修改q的前后节点
    q->next = n;
    q->prior = p;

    // 将q节点放置于节点n和p之间
    p->next = q;
    if (n != NULL) n->prior = q;

    return SUCCESS;
}

/* 将节点p后的第一个节点删除，并将其值保留至e */
Status DeleteList_DuL(DuLNode *p, ElemType *e) {
    if (p == NULL || p->next == NULL) return ERROR;

    DuLNode *n = p->next, *q = n->next;

    p->next = q;
    if (q != NULL) q->prior = p;

    *e = n->data;

    free(n);
}

/* 遍历指针并引用函数visit */
void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
    DuLNode *p = L->next;

    printf("\nR:");
    // 向下遍历
    while (p != NULL) {
        visit(p->data);
        p = p->next;
    }

    printf("\nL:");
    p = L->prior;

    // 向上遍历
    while (p != NULL) {
        visit(p->data);
        p = p->prior;
    }
}
