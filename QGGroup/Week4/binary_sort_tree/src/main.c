#include <stdio.h>
#include <stdlib.h>
#include "../inc/binary_sort_tree.h"

char ch_menu[14][50] = {
    "Here are functions you can use:",
    "A.BST_init",
    "B.BST_insert",
    "C.BST_delete",
    "D.BST_search",
    "E.BST_preorderI",
    "F.BST_preorderR",
    "G.BST_inorderI",
    "H.BST_inorderR",
    "I.BST_postorderI",
    "J.BST_postorderR",
    "K.BST_levelOrder",
    "L.Quit",
    "Please enter the function you want to use:"

};

typedef struct Stack {
    NodePtr node;
    struct Stack* next;
} Stack, *StackPtr;

typedef struct LinkStack {
    struct Stack* link;
} LinkStack, *LinkStackPtr;

typedef struct Queue {
    NodePtr node;
    struct Queue* next;
    struct Queue* prior;
} Queue, *QueuePtr;

typedef struct LinkQueue {
    struct Queue* linktop;
    struct Queue* linkend;
} LinkQueue, *LinkQueuePtr;

Status InitStack(LinkStackPtr s);
Status PushStack(LinkStackPtr s, NodePtr node);
Status PopStack(LinkStackPtr s);
NodePtr TopStack(LinkStackPtr s);
Status PushQueue(LinkQueuePtr q, NodePtr node);
Status PopQueue(LinkQueuePtr q);
NodePtr EndQueue(LinkQueuePtr q);
Status InitQueue(LinkQueuePtr q);
void BST_Func(NodePtr node);

int main() {
    BinarySortTreePtr p = NULL;
    void(*visit)(NodePtr);
    visit = BST_Func;

    while (1) {
        for (int i = 0; i < 14; i++) {
            puts(ch_menu[i]);
        }

        char key = getchar();

        switch (key) {
        case 'A':
        case 'a': {
            p = (BinarySortTree*)malloc(sizeof(BinarySortTree));
            BST_init(p);
            printf("Binary Sort Tree init succeed.");
            break;
        }
        case 'B':
        case 'b': {
            ElemType data;
            printf("Please enter the data you want to insert:");
            scanf_s("%d", &data);
            if (BST_insert(p, data)) printf("Inserting succeed!");
            else printf("Inserting failed, have you inited the tree?");
            break;
        }
        case 'C':
        case 'c': {
            ElemType data;
            printf("Please enter the data you want to delete:");
            scanf_s("%d", &data);
            if (BST_delete(p, data)) printf("deleting succeed!");
            else printf("deleting failed, have you inited the tree?");
            break;
        }
        case 'D':
        case 'd': {
            ElemType data;
            printf("Please enter the data you want to search:");
            scanf_s("%d", &data);
            if (BST_search(p, data)) printf("%d exist.");
            else printf("Searching failed, have you inited the tree?");
            break;
        }
        case 'E':
        case 'e': {
            printf("Here are the result of preorder without recursion\n");
            BST_preorderI(p, visit);
            break;
        }
        case 'F':
        case 'f': {
            printf("Here are the result of preorder with recursion\n");
            BST_preorderR(p->root, visit);
            break;
        }
        case 'G':
        case 'g': {
            printf("Here are the result of inorder without recursion\n");
            BST_inorderI(p, visit);
            break;
        }
        case 'H':
        case 'h': {
            printf("Here are the result of inorder with recursion\n");
            BST_inorderR(p->root, visit);
            break;
        }
        case 'I':
        case 'i': {
            printf("Here are the result of postorder without recursion\n");
            BST_postorderI(p, visit);
            break;
        }
        case 'J':
        case 'j': {
            printf("Here are the result of postorder with recursion\n");
            BST_postorderR(p->root, visit);
            break;
        }
        case 'K':
        case 'k': {
            printf("Here are the result of levelOrder\n");
            BST_levelOrder(p, visit);
            break;
        }
        case 'L':
        case 'l': {
            return 0;
            }
        default: break;
        }

        printf("\n");
        getchar();
    }
    return 0;
}

Status InitStack(LinkStackPtr s) {
    if (s == NULL) return failed;

    s->link = NULL;

    return succeed;
}

Status PushStack(LinkStackPtr s, NodePtr node) {
    if (s == NULL) return failed;

    StackPtr newstack = (Stack*)malloc(sizeof(Stack));;

    newstack->next = s->link;

    newstack->node = node;

    s->link = newstack;

    return succeed;
}

Status PopStack(LinkStackPtr s) {
    if (s == NULL) return failed;

    if (s->link == NULL) return failed;

    StackPtr oldstack = s->link;
    s->link = oldstack->next;

    free(oldstack);

    return succeed;
}

NodePtr TopStack(LinkStackPtr s) {
    if (s == NULL) return NULL;

    return s->link->node;
}

Status IsStackEmety(LinkStackPtr s) {
    if (s->link == NULL) return succeed;
    return failed;
}

Status InitQueue(LinkQueuePtr q) {

    if (q == NULL) return failed;

    q->linktop = NULL;
    q->linkend = NULL;

    return succeed;

}

Status PushQueue(LinkQueuePtr q, NodePtr node) {

    if (q == NULL) return failed;

    QueuePtr newqueue = (Queue*)malloc(sizeof(Queue));;

    newqueue->next = q->linktop;
    newqueue->prior = NULL;

    if (q->linktop != NULL) {
        q->linktop->prior = newqueue;
    }

    newqueue->node = node;

    if (q->linktop == NULL) q->linkend = newqueue;

    q->linktop = newqueue;

    return succeed;

}

Status PopQueue(LinkQueuePtr q) {
    if (q == NULL) return failed;

    if (q->linktop == NULL) return failed;

    QueuePtr oldstack = q->linkend;
    q->linkend = oldstack->prior;
    if (q->linkend != NULL) q->linkend->next = NULL;
    else q->linktop = NULL;

    free(oldstack);

    return succeed;
}

NodePtr EndQueue(LinkQueuePtr q) {
    if (q == NULL) return NULL;

    return q->linkend->node;
}

Status IsQueueEmety(LinkQueuePtr q) {

    if (q == NULL) return failed;

    if (q->linkend != NULL) return failed;
    else return succeed;
}

void BST_Func(NodePtr node) {

    if (node == NULL) return failed;

    printf("%d ", node->value);
    return succeed;
}

Status BST_init(BinarySortTreePtr ptree) {
    if (ptree == NULL) return failed;

    ptree->root = NULL;

    return succeed;
}

Status BST_insert(BinarySortTreePtr ptree, ElemType data) {
    if (ptree == NULL) return failed;

    // pnode_parent为pnode的父母节点
    NodePtr pnode = ptree->root;
    NodePtr pnode_parent = pnode;

    // 寻找插入位置
    while (pnode != NULL) {
        pnode_parent = pnode;

        if (data < pnode->value) {
            pnode = pnode->left;
            continue;
        }

        if (data > pnode->value) {
            pnode = pnode->right;
            continue;
        }

        // 树内有相同值节点，插入失败
        if (data == pnode->value) {
            return failed;
        }
    }

    if (pnode_parent == NULL) {
        // 首节点为空，直接新建
        pnode = ptree->root = (Node*)malloc(sizeof(Node));

    } else if (data < pnode_parent->value) {
        // 插入位置在pnode_parent的左边，新建节点
        pnode = pnode_parent->left = (Node*)malloc(sizeof(Node));

    } else if (data > pnode_parent->value) {
        // 插入位置在pnode_parent的右边，新建节点
        pnode = pnode_parent->right = (Node*)malloc(sizeof(Node));

    }

    // 赋值初始化
    pnode->value = data;
    pnode->left = NULL;
    pnode->right = NULL;

    return succeed;
    
}

Status BST_delete(BinarySortTreePtr ptree, ElemType data) {
    if (ptree == NULL || ptree->root == NULL) return failed;

    NodePtr goalnode = ptree->root;
    NodePtr goalnode_parent = goalnode;

    // 寻找该值在树中的对应位置
    while (goalnode != NULL) {

        if (data == goalnode->value) break;

        goalnode_parent = goalnode;

        if (data < goalnode->value) {
            goalnode = goalnode->left;
            continue;
        }

        if (data > goalnode->value) {
            goalnode = goalnode->right;
            continue;
        }
    }

    // 如果未找到该节点，返回错误
    if (goalnode_parent != data && goalnode == NULL) return failed;

    // 如果该节点无子，直接删除
    if (goalnode->left == NULL && goalnode->right == NULL) {

        // 如果删除的为树的唯一节点，特殊处理
        if (data == goalnode_parent->value) {
            ptree->root = NULL;
            free(goalnode);
            return succeed;
        }

        if (data < goalnode_parent->value) {
            goalnode_parent->left = NULL;
        }

        if (data > goalnode_parent->value) {
            goalnode_parent->right = NULL;
        }

        free(goalnode);

        return succeed;
    }

    // 如果该节点有两子，寻找其直接后继并替换
    if (goalnode->left != NULL && goalnode->right != NULL) {

        NodePtr successor = goalnode->right;
        NodePtr successor_parent = successor;

        while (successor->left != NULL) {
            successor_parent = successor;
            successor = successor->left;
        }

        // 如果继承为节点的右支
        // 由该右支继承节点，并继承节点左支为右支的左支
        if (goalnode->right == successor) {
            successor->left = goalnode->left;

            // 删除的为根节点，特殊处理
            if (ptree->root == goalnode) {
                ptree->root = successor;
                free(goalnode);
                return succeed;
            }

            if (successor->value < goalnode_parent->value) goalnode_parent->left = successor;

            if (successor->value > goalnode_parent->value) goalnode_parent->right = successor;

            free(goalnode);

            return succeed;
        }

        goalnode->value = successor->value;
        
        successor_parent->left = successor->right;

        free(successor);

        return succeed;
    }

    // 如果该节点有一子，该子继承该节点
    if (goalnode->left != NULL || goalnode->right != NULL) {

        NodePtr successor;
        if (goalnode->left != NULL) {
            successor = goalnode->left;
        }
        else if (goalnode->right != NULL) {
            successor = goalnode->right;
        }

        //如果删除的为树根节点，特殊处理
        if (ptree->root == goalnode) {
            ptree->root = successor;
            free(goalnode);
            return succeed;
        }

        if (goalnode_parent->left == goalnode) {
            goalnode_parent->left = successor;
            free(goalnode);
            return succeed;
        }

        if (goalnode_parent->right == goalnode) {
            goalnode_parent->right = successor;
            free(goalnode);
            return succeed;
        }
        
        return failed;
    }
}

Status BST_search(BinarySortTreePtr ptree, ElemType data) {

    if (ptree == NULL || ptree->root == NULL) return failed;

    NodePtr current = ptree->root;

    // 查询是否存在该数
    while (current != NULL) {
        if (data < current->value) current = current->left;

        if (data > current->value) current = current->right;

        if (data == current->value) return succeed;
    }

    return failed;
}


Status BST_preorderI(BinarySortTreePtr ptree, void (*visit)(NodePtr)) {

    if (ptree == NULL || ptree->root == NULL) return failed;

    // 栈注册
    LinkStackPtr stack = (LinkStack*)malloc(sizeof(LinkStack));
    InitStack(stack);

    PushStack(stack, ptree->root);
    NodePtr current = ptree->root;

    while (!IsStackEmety(stack)) {
        current = TopStack(stack);
        visit(current);
        PopStack(stack);
        if (current->right != NULL) PushStack(stack, current->right);
        if (current->left != NULL) PushStack(stack, current->left);
    }

    return succeed;
}


Status BST_preorderR(NodePtr pnode, void (*visit)(NodePtr)) {

    if (pnode == NULL) return failed;

    visit(pnode);
    BST_preorderR(pnode->left, visit);
    BST_preorderR(pnode->right, visit);

    return succeed;
}

Status BST_inorderI(BinarySortTreePtr ptree, void (*visit)(NodePtr)) {

    if (ptree == NULL || ptree->root == NULL) return failed;

    // 栈注册
    LinkStackPtr stack = (LinkStack*)malloc(sizeof(LinkStack));
    InitStack(stack);

    NodePtr current = ptree->root;

    // 将左叉全部压入栈中
    while (current != NULL) {
        PushStack(stack, current);
        current = current->left;
    }

    // 弹出栈的头元素，输出并检查其是否有右节点
    // 有则压入并遍历其左支
    while (!IsStackEmety(stack)) {
        current = TopStack(stack);
        PopStack(stack);
        visit(current);
        
        if (current->right != NULL) {
            current = current->right;

            while (current != NULL) {
                PushStack(stack, current);
                current = current->left;
            }
        }
    }

    return succeed;

}

Status BST_inorderR(NodePtr pnode, void (*visit)(NodePtr)) {

    if (pnode == NULL) return failed;

    BST_inorderR(pnode->left, visit);
    visit(pnode);
    BST_inorderR(pnode->right, visit);

    return succeed;

}

Status BST_postorderI(BinarySortTreePtr ptree, void (*visit)(NodePtr)) {

    if (ptree == NULL || ptree->root == NULL) return failed;

    // 栈注册
    LinkStackPtr stack = (LinkStack*)malloc(sizeof(LinkStack));
    InitStack(stack);

    NodePtr current = ptree->root, rightnode = NULL;

    while (current != NULL || !IsStackEmety(stack)) {

        // 如果当前节点有左节点，一路向下
        if (current != NULL) {
            PushStack(stack, current);
            current = current->left;
        }

        // 如果没有左节点
        else {

            // 如果当前节点有右节点，且右节点未去过
            current = TopStack(stack);
            if (current->right && current->right != rightnode) {

                // 前往右节点
                current = current->right;
            }
            else {

                //否则输出该节点，标记该节点为去过的右节点并重置当前节点
                PopStack(stack);
                visit(current);
                rightnode = current;
                current = NULL;
            }
        }
    }

    return succeed;

}

Status BST_postorderR(NodePtr pnode, void (*visit)(NodePtr)) {

    if (pnode == NULL) return failed;

    BST_postorderR(pnode->left, visit);
    BST_postorderR(pnode->right, visit);
    visit(pnode);

    return succeed;

}

Status BST_levelOrder(BinarySortTreePtr ptree, void (*visit)(NodePtr)) {

    if (ptree == NULL || ptree->root == NULL) return failed;

    // 队列注册
    LinkQueuePtr queue = (LinkQueue*)malloc(sizeof(LinkQueue));
    InitQueue(queue);
    NodePtr current = ptree->root;
    PushQueue(queue, current);

    while (!IsQueueEmety(queue)) {
        current = EndQueue(queue);
        PopQueue(queue);
        visit(current);
        if (current->left != NULL) PushQueue(queue, current->left);
        if (current->right != NULL) PushQueue(queue, current->right);

    }

    return succeed;
}
