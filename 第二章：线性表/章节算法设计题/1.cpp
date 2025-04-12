/*

题目
将两个非递减的有序链表合并为一个递增的有序链表。要求结果链表仍使用原来两个链表的存储空间，不占用其他的存储空间。
表中不允许有重复的数据

思路：框架是原先有序表合并的基础，如果相等就只接入一个值

*/

#include <stdio.h>
#include <stdlib.h>

#define ok 1
#define error 0
#define overflows -1

typedef int status;
typedef int elemtype;

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

status mergelist(linklist &la, linklist &lb, linklist &lc)
{
    lc = la;             // 不额外使用空间，直接使用 a 的头节点作为新链表 c 的头节点
    lnode *pa, *pb, *pc; // 定义头指针，确定一个链表
    pa = la->next;
    pb = lb->next;
    pc = lc; // 不直接对头指针进行修改，引入新的变量代替
    while (pa && pb)
    {
        if (pa->data < pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else if (pb->data < pa->data)
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
        else
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
            pb = pb->next;
        }
        if (pa)
        {
            pc->next = pa;
        }
        else
        {
            pc->next = pb;
        }
    }
    lnode *print;
    print = lc->next;
    printf("merge result print below :");
    while (print)
    {
        printf("%d ", print->data);
        print = print->next;
    }
    return ok;
}

int main()
{
    lnode *a, *b, *c;
    printf("la init\n");
    listinit(a);
    printf("\n");
    printf("lb init\n");
    printf("\n");
    listinit(b);
    mergelist(a, b, c);
    printf("\n");
}