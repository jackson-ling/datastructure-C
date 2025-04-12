/*

题目：通过一趟遍历确定长度为n的单链表中值最大的节点

*/

#include <stdio.h>
#include <stdlib.h>

typedef int status;
typedef int elemtype;

#define ok 1
#define error
#define overflows -1

typedef struct lnode
{
    elemtype data;
    struct lnode *next;
} lnode, *linklist;

status listinit(linklist &l)
{
    l = (lnode *)malloc(sizeof(lnode));
    l->next = NULL;
    if (!l)
    {
        return overflows;
    }
    lnode *q;
    q = l;
    printf("init success\n");
    printf("\n");
    printf("how many data do you want to input this time:");
    int n;
    scanf("%d", &n);
    printf("\n");
    printf("input data:");
    for (int i = 0; i < n; i++)
    {
        lnode *p;
        p = (lnode *)malloc(sizeof(lnode));
        p->next = NULL;
        scanf("%d", &p->data);
        q->next = p;
        q = p;
    }
    printf("\n");
    return ok;
}

status maxnode(linklist l)
{
    lnode *p;
    int j = 1;
    p = l->next;
    int max = p->data; // 假设第一个节点最大，只要由更大的就更新
    int maxnode = j;
    p = p->next; // 从第二个节点开始遍历
    j++;         // 初始位置是第二个节点
    if (p == NULL)
    {
        printf("list is empty\n");
        return error;
    }
    while (p != NULL)
    {
        if (p->data > max)
        {
            max = p->data;
            maxnode = j; // 更新最大节点的位置
        }
        p = p->next;
        j++;
    }
    printf("the maxnode is :%d", maxnode);
    printf("\n");
    return ok;
}

int main()
{
    lnode *l;
    listinit(l);
    printf("\n");
    maxnode(l);
    printf("\n");
}