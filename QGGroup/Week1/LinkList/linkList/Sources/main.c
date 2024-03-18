/*
    File Name: main.c
    Be writen on ArchLinux

*/

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

// 为WINDOWS或LINUX系统不同定义
#ifdef _WIN32
#define CLEARSCREEN "cls"
#endif
#ifdef __linux__
#define CLEARSCREEN "clear"
#endif

// 界面字符数组
char char_menu[12][50] = {
    "Here are all function you can use to LinkList:",
    "A.InitList",
    "B.DestroyList",
    "C.InsertList",
    "D.DeleteList",
    "E.TraverseList(CheckList)",
    "F.SearchList",
    "G.ReverseList",
    "H.IsLoopList",
    "I.ReverseEvenList",
    "J.FindMidNode",
    "Please choose the function:(A-J)"};

void printValue(ElemType e);
void FuncMenu();

int main()
{
    FuncMenu();

    return 0;
}

// 功能面板，操作所有功能
void FuncMenu()
{
    // 声明指针
    LinkedList *p = (LinkedList *)malloc(sizeof(LinkedList));
    ElemType *cache = (ElemType *)malloc(sizeof(ElemType));
    LNode *n;
    void (*visit)(ElemType) = printValue;

    char ch;

    while (1)
    {

        // 打印界面
        for (int i = 0; i < 12; i++)
        {
            puts(char_menu[i]);
        }

        // 排除回车
        do
        {
            ch = getchar();
        } while (ch == '\n');

        switch (ch)
        {
        case 'A':
            if (!InitList(p)) {
                printf("The creation has failed!\n");
            } else {
                printf("The creation is successed.\n");
            }
            break;
        case 'B':
            DestroyList(p);
            printf("The Destroy is completed.\n");
            break;
        case 'C':
            n = (LNode *)malloc(sizeof(LNode));
            printf("Please enter the data of the new node:");
            scanf("%d", &n->data);
            n->next = NULL;
            InsertList(*p, n);
            printf("The new node has inserted.\n");
            break;
        case 'D':
            DeleteList(*p, cache);
            printf("Deleted the node after head node, its data is %d", *cache);
            break;
        case 'E':
            printf("The LinkList:");
            TraverseList(*p, visit);
            break;
        case 'F':
            printf("Does the linklist include data: %d? The ans is: %d", SUCCESS, SearchList(*p, SUCCESS));
            break;
        case 'G':
            ReverseList(p);
            printf("The linklist has been reversed.\n");
            break;
        case 'H':
            printf("Is the list loop?: %d", IsLoopList(*p));
            break;
        case 'I':
            (*p)->next = ReverseEvenList(p);
            printf("The linklist has been reversed even.\n");
            break;
        case 'J':
            n = FindMidNode(p);
            printf("The data of mid node is: %d", n->data);
            break;

        default:
            printf("%c:no opinion!\n", ch);
            break;
        }

        // 不接收回车，同时保留输出结果
        getchar();
        getchar();
        system(CLEARSCREEN);
    }
}

/* 打印节点值 */
void printValue(ElemType e)
{
    printf("%d ", e);
}

/* 初始化链表指针 */
Status InitList(LinkedList *L)
{

    // 如果L本身为空指针，返回错误
    if (L == NULL)
        return ERROR;

    *L = (LNode *)malloc(sizeof(LNode));

    // 如果L指向的指针为空（没有申请到内存），返回错误
    if ((*L) == NULL)
        return ERROR;

    (*L)->data = -1;
    (*L)->next = NULL;

    return SUCCESS;
}

/* 删除链表指针 */
void DestroyList(LinkedList *L)
{

    // p1用于存储当前节点地址，p2用于存储下一节点地址
    LNode *p1, *p2;
    p1 = *L;
    p2 = (*L)->next;

    while (1)
    {

        // 将当前节点释放
        free(p1);

        // 如果下一节点为空（遇到表尾），结束循环
        if (p2 == NULL)
            break;

        // 否则将下一节点作为当前节点，下下节点作为下一节点
        p1 = p2;
        p2 = p2->next;
    }
}

/* 将节点q插入到节点p后 */
Status InsertList(LNode *p, LNode *q)
{

    // 如果p节点本身为空，返回错误
    if (p == NULL)
        return ERROR;

    q->next = p->next;
    p->next = q;

    return SUCCESS;
}

/* 将节点p后的第一个节点删除，并将其值保留至e */
Status DeleteList(LNode *p, ElemType *e)
{
    LNode *n = p->next;
    *e = n->data;

    p->next = n->next;

    free(n);
}

/* 遍历指针并引用函数visit */
void TraverseList(LinkedList L, void (*visit)(ElemType e))
{
    LNode *n = L;

    while (n != NULL)
    {
        visit(n->data);
        n = n->next;
    }
}

/* 找到符合e的第一个节点 */
Status SearchList(LinkedList L, ElemType e)
{
    LNode *n = L;

    while (n != NULL)
    {
        if (n->data == e)
            return SUCCESS;
        n = n->next;
    }

    return ERROR;
}

/* 反转链表，反转不包括头节点的部分 */
Status ReverseList(LinkedList *L)
{
    LNode *PL, *PM, *PR;

    // 如果头节点为空或者首节点为空，返回错误
    if (L == NULL || (*L)->next == NULL)
        return ERROR;

    // 初始化节点指针
    // 这里PL PM PR分别代表反转前所顺序选择的三个节点
    PL = PM = NULL;
    PR = (*L)->next;

    do
    {
        // 将PL PM PR三个指针前移
        PL = PM;
        PM = PR;
        PR = PR->next;

        // 将PM的下个节点指向PL
        PM->next = PL;

        // 当PR为空节点时退出
    } while (PR != NULL);

    // 重新指定链表头的下一个节点
    (*L)->next = PM;

    return SUCCESS;
}

/* 返回链表是否循环 */
Status IsLoopList(LinkedList L)
{

    // 使用快慢指针
    LNode *pslow = L, *pfast = L;

    do
    {
        // 快指针前进两次，每次都检查
        pfast = pfast->next;
        if (pfast == NULL)
            return ERROR;
        pfast = pfast->next;
        if (pfast == NULL)
            return ERROR;

        // 慢指针前进一次
        pslow = pslow->next;

        // 两指针相遇时退出
    } while (pfast != pslow);

    return SUCCESS;
}

/* 反转奇偶节点 */
LNode *ReverseEvenList(LinkedList *L)
{

    // PL PM PR 分别为原链表的顺序三个节点
    LNode *PL = *L, *PM, *PR;

    // 如果链表只有头节点和下一个节点，返回该节点
    if (PL->next == NULL || PL->next->next == NULL)
        return PL;

    // 初始化PM，PR指针
    PM = PL->next;
    PR = PM->next;

    do
    {
        // 扭转顺序，使PL PM PR 变为 PL PR PM
        PL->next = PR;
        PM->next = PR->next;
        PR->next = PM;

        // 将PL PM PR 往后移
        // 注意现在是将PL PR PM迁移变为PL(原PM) PM PR
        PL = PM;
        PM = PM->next;

        // 如果PM为表尾，退出
        if (PM == NULL) break;
        PR = PM->next;
        
    } while (PR != NULL);

    return (*L)->next;
}

/* 寻找中节点 */
LNode *FindMidNode(LinkedList *L)
{

    // 使用快慢节点
    LNode *PM = *L, *PR = *L;
    int count = 0;

    while (PR != NULL)
    {
        // 快节点每次移动
        PR = PR->next;
        count++;
        if (count % 2 == 0)
        {
            // 慢节点两次移动一次
            PM = PM->next;
        }
    }

    // 返回慢节点
    return PM;
}
