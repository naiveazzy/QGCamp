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

    // pnode_parentΪpnode�ĸ�ĸ�ڵ�
    NodePtr pnode = ptree->root;
    NodePtr pnode_parent = pnode;

    // Ѱ�Ҳ���λ��
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

        // ��������ֵͬ�ڵ㣬����ʧ��
        if (data == pnode->value) {
            return failed;
        }
    }

    if (pnode_parent == NULL) {
        // �׽ڵ�Ϊ�գ�ֱ���½�
        pnode = ptree->root = (Node*)malloc(sizeof(Node));

    } else if (data < pnode_parent->value) {
        // ����λ����pnode_parent����ߣ��½��ڵ�
        pnode = pnode_parent->left = (Node*)malloc(sizeof(Node));

    } else if (data > pnode_parent->value) {
        // ����λ����pnode_parent���ұߣ��½��ڵ�
        pnode = pnode_parent->right = (Node*)malloc(sizeof(Node));

    }

    // ��ֵ��ʼ��
    pnode->value = data;
    pnode->left = NULL;
    pnode->right = NULL;

    return succeed;
    
}

Status BST_delete(BinarySortTreePtr ptree, ElemType data) {
    if (ptree == NULL || ptree->root == NULL) return failed;

    NodePtr goalnode = ptree->root;
    NodePtr goalnode_parent = goalnode;

    // Ѱ�Ҹ�ֵ�����еĶ�Ӧλ��
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

    // ���δ�ҵ��ýڵ㣬���ش���
    if (goalnode_parent != data && goalnode == NULL) return failed;

    // ����ýڵ����ӣ�ֱ��ɾ��
    if (goalnode->left == NULL && goalnode->right == NULL) {

        // ���ɾ����Ϊ����Ψһ�ڵ㣬���⴦��
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

    // ����ýڵ������ӣ�Ѱ����ֱ�Ӻ�̲��滻
    if (goalnode->left != NULL && goalnode->right != NULL) {

        NodePtr successor = goalnode->right;
        NodePtr successor_parent = successor;

        while (successor->left != NULL) {
            successor_parent = successor;
            successor = successor->left;
        }

        // ����̳�Ϊ�ڵ����֧
        // �ɸ���֧�̳нڵ㣬���̳нڵ���֧Ϊ��֧����֧
        if (goalnode->right == successor) {
            successor->left = goalnode->left;

            // ɾ����Ϊ���ڵ㣬���⴦��
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

    // ����ýڵ���һ�ӣ����Ӽ̳иýڵ�
    if (goalnode->left != NULL || goalnode->right != NULL) {

        NodePtr successor;
        if (goalnode->left != NULL) {
            successor = goalnode->left;
        }
        else if (goalnode->right != NULL) {
            successor = goalnode->right;
        }

        //���ɾ����Ϊ�����ڵ㣬���⴦��
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

    // ��ѯ�Ƿ���ڸ���
    while (current != NULL) {
        if (data < current->value) current = current->left;

        if (data > current->value) current = current->right;

        if (data == current->value) return succeed;
    }

    return failed;
}


Status BST_preorderI(BinarySortTreePtr ptree, void (*visit)(NodePtr)) {

    if (ptree == NULL || ptree->root == NULL) return failed;

    // ջע��
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

    // ջע��
    LinkStackPtr stack = (LinkStack*)malloc(sizeof(LinkStack));
    InitStack(stack);

    NodePtr current = ptree->root;

    // �����ȫ��ѹ��ջ��
    while (current != NULL) {
        PushStack(stack, current);
        current = current->left;
    }

    // ����ջ��ͷԪ�أ������������Ƿ����ҽڵ�
    // ����ѹ�벢��������֧
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

    // ջע��
    LinkStackPtr stack = (LinkStack*)malloc(sizeof(LinkStack));
    InitStack(stack);

    NodePtr current = ptree->root, rightnode = NULL;

    while (current != NULL || !IsStackEmety(stack)) {

        // �����ǰ�ڵ�����ڵ㣬һ·����
        if (current != NULL) {
            PushStack(stack, current);
            current = current->left;
        }

        // ���û����ڵ�
        else {

            // �����ǰ�ڵ����ҽڵ㣬���ҽڵ�δȥ��
            current = TopStack(stack);
            if (current->right && current->right != rightnode) {

                // ǰ���ҽڵ�
                current = current->right;
            }
            else {

                //��������ýڵ㣬��Ǹýڵ�Ϊȥ�����ҽڵ㲢���õ�ǰ�ڵ�
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

    // ����ע��
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
