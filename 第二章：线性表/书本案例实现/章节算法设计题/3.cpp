/*

题目：已知两个链表A和B分别表示两个集合，其元素递增排列。请设计一个算法，用于求出A与B的交集，并将结果放在A链表中


思路：
1.求交集：分别遍历两个链表，只要是元素相同就放到a链表中

如何理解交集放在a中？
（1）首先需要使用a链表本身，不可以申请额外的空间，就说明需要对链表进行删除操作
（2）枚举一些例子发现：如果元素不相等，可能  a>b  ，可能  a<b  ，这个时候如何才处理才能实现在后续的数中可能出现的交集


2.不会的地方：如何实现当遍历数不一样的时候求交集————需要抓住数是逐渐递增的特性
（1）如果a=b，直接保留a节点————a指针后移，b指针后移

当两个数不相等的时候，需要抓住一个核心，让两个数的大小靠近，这样才可能出现交集的情况

（2）如果a<b，根据递增的特点，在b当前之后的元素都必然会比a大，就不能出现交集————删除a节点，a指针后移，b指针不动
（3）如果a>b，根据递增的特点，只有b的值增大才可能出现相等的情况，此时a不动，b指针后移

本题的易错点：需要用前驱指针来实现删除操作，如果用新的指针保存要删除的节点同时指针后移，那在要删除节点之前的元素就
             会无法与后面链接，进而破坏了链表的结构，这里使用前驱指针的思想和链表的删除思想类似，不同的是，
             使用前驱指针时，指针直接指向了要删除的元素，这时只要先修改指针再释放节点即可，不需要找到第i-1个
             节点

反思延申：在需要保证链表完整性的情况下，对链表进行插入和删除操作都需要前驱指针，修改指针来保证链表的完整性，即
         保证每一个节点都链接了下一个节点，不会出现找不到下一个节点的地址的情况
*/

#include<stdio.h>
#include<stdlib.h>

typedef int status;
typedef int elemtype;

#define ok 1
#define error 0
#define overflow -1

typedef struct lnode
{
    elemtype data;
    struct lnode *next;
}lnode,*linklist;

void printlist(linklist l)
{
    lnode *p;
    p=l->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
}

//初始化+录入元素
status listinit(linklist &l)
{
    l=(lnode*)malloc(sizeof(lnode));
    l->next=NULL;
    if(!l)
    {
        printf("fail to init\n");
        return overflow;
    }

    //使用后插法建立链表，并实现数的录入
    int n;
    lnode *p,*s;
    //易错：刚创建完链表，此时next域是空的，初始是应该p=l（指向头节点，并非首元节点，需要创建之后才首元节点）
    p=l;
    printf("how many data do you want to input in this lnode:");
    scanf("%d",&n);
    printf("\n");
    printf("please input data in this lnode:");
    for(int i=0;i<n;i++)
    {
        s=(lnode*)malloc(sizeof(lnode));
        s->next=NULL;
        scanf("%d",&s->data);
        p->next=s;
        p=s;
    }
    printf("\n");
    printlist(l);
    printf("\n");
    return ok;
}

status mergelist(linklist la,linklist lb)
{
    //分别遍历两个链表

    lnode *p,*q,*pre;
    pre=la;//作为q的前驱指针，为了保证在进行插入和删除后链表的完整性，需要一个前驱指针
    p=la->next;
    q=lb->next;
    while(p&&q)
    {
        //如果a=b，直接保留a节点————a指针后移，b指针后移
        if(p->data==q->data)
        {
            pre=p;
            p=p->next;
            q=q->next;
        }
        //如果a<b，根据递增的特点，在b当前之后的元素都必然会比a大，就不能出现交集————删除a节点，a指针后移，b指针不动
        else if(p->data<q->data)
        {
            lnode *s;
            s=p;
            p=p->next;
            pre->next=p;//要删除的节点用新指针保存后，同时修改删除节点的前驱指针，和链表的删除思想保持一致
            free(s);
        }
        //如果a>b，根据递增的特点，只有b的值增大才可能出现相等的情况，此时a不动，b指针后移
        else
        {
            q=q->next;
        }
    }
    
    //还需要考虑一种情况，b遍历完成了，但是a还有剩余节点，这个时候需要删除剩余节点
    while(p)
    {
        lnode *s;
        s=p;;
        p=p->next;
        pre->next=p;
        free(s);
    }
    printf("\n");

    printf("The result of the intersection of two sets is as follows:\n");
    //注意打印结果的逻辑，应该是在合并完成后
    printlist(la);
    printf("\n");

    //做一个性能优化，交集放在a之后，把lb也释放掉，这样可以优化空间性能
    lnode *temp;
    temp=lb;
    while(temp)
    {
        lb=lb->next;
        free(temp);//初始时指向头节点，头节点也被删除了
    }
    return ok;
}

int main()
{
    lnode *la,*lb;
    listinit(la);
    printf("\n");
    listinit(lb);
    mergelist(la,lb);
}