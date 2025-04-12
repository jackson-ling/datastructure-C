/*

题目
将两个非递减的有序链表合并为一个非递增的有序链表。要求结果链表仍使用原来两个链表的存储空间，不另外占用其他的存储空间。
表中允许有重重复的数据

简单一句话：把两个递增的合并成递减的，只要从最大的开始往前遍历，大的优先放进去，小的自然就跟在后面了

易错：指针指的是节点，不能像数组一样使用指针偏移，由于是单项链表，需要使用前驱节点，这个时候引入前驱指针即可

考虑到前驱指针的复杂性，换个思路，既然结果是递减的，那直接先合成递增的，修改头指针指向尾节点，那不就是递减大的

问题又来了，指针的方向始终没有变化，还是需要前驱指针，咋办？

在添加节点到lc的时候用前插法，小的先添加，大的添加在小的前面，完美解决
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
        printf("fail to init\n");
        return overflows;
    }
    printf("init success\n");
    printf("\n");
    lnode *q;
    q = l;
    int n;
    printf("how many data do you want to input:");
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

// lnode *gettaildata(linklist l)
// {
//     lnode *p;
//     p = l;
//     if (p == NULL)
//     {
//         return NULL;
//     }
//     while (p->next != NULL) // 易错：如果是p，最后返回的p是空，因为是循环的结束条件
//     {
//         p = p->next;
//     }
//     return p;
// }

status mergelist(linklist &la, linklist &lb, linklist &lc)
{
    lnode *pa, *pb, *pc;
    lc = la;
    pa = la->next;
    pb = lb->next;
    pc = lc;
    while (pa && pb)
    {
        // 注意逻辑：是把大的那个节点前插
        if (pa->data > pb->data)
        {
            pa->next = pc->next;
            pc->next = pa;
            pa = pa->next;
        }
        else if (pb->data > pa->data)
        {
            pb->next = pc->next;
            pc->next = pb;
            pb = pb->next;
        }
        else
        {
            pa->next = pc->next;
            pc->next = pa;
            pa = pa->next;
            pb = pb->next;
        }
    }
    // 如果pa链表还有剩余，直接插入
    while (pa)
    {
        pa->next = pc->next;
        pc->next = pa;
        pa = pa->next;
    }

    // 如果pb链表还有剩余，直接插入
    while (pb)
    {
        pb->next = pc->next;
        pc->next = pb;
        pb = pb->next;
    }

    lnode *print;
    print = lc->next;
    printf("merge result :");
    while (print)
    {
        printf("%d", print->data);
        print = print->next;
    }
    printf("\n");
    return ok;
}

int main()
{
    lnode *la, *lb, *lc;
    printf("la init\n");
    printf("\n");
    listinit(la);
    printf("\n");
    printf("lb init\n");
    printf("\n");
    listinit(lb);
    printf("\n");
    mergelist(la, lb, lc);
    printf("\n");
}