#include<stdio.h>
#include<stdlib.h>

#define ok 1
#define error 0
#define overflow -1

typedef int status;
typedef int elemtype;

//链表的定义
typedef struct lnode
{
    elemtype data;
    struct lnode *next;
}lnode,*linklist;


//链表的初始化+值的录入
status listinit(linklist &l)
{
    int n;
    l=(lnode *)malloc(sizeof(lnode));
    l->next=NULL;
    if(!l)
    {
        return overflow;
    }
    lnode *p,*s;
    printf("how many data do you want to input:");
    scanf("%d",&n);
    p=l;
    printf("input data in this lnode:");
    printf("\n");
    for(int i=0;i<n;i++)
    {
        s=(lnode *)malloc(sizeof(lnode));
        scanf("%d",&s->data);
        s->next=NULL;  //创建一个新的节点，注意把指针域置空，方便下一个节点的插入
        p->next=s;
        p=s;
    }
    printf("input success\n");
    return ok;
}

//说明：由于链表的插入很灵活，这里是在新的链表里插入节点（用尾插法），不需要单独写插入操作

//有序表合并操作
status mergelist(linklist &la,linklist &lb,linklist &lc)
{
    lnode *pa,*pb,*pc;
    pa=la->next;
    pb=lb->next;
    //为了避免重新分配空间，直接使用头节点a作为新链表lc的首元节点
    lc=la;//用la的头节点作为lc的头节点，此时头指针lc指向la的头节点（la原先就是指向la的头节点）
    pc=lc;//引入新的指针，指向头节点

    //接下来开始比较值的大小，组个插入到新的链表C中
    while(pa&&pb)
    {
        if(pa->data<=pb->data) //注意这里的等于
        {
            pc->next=pa;
            pc=pa;
            pa=pa->next;//pa和pb两个指针的作用是比较两个数值的大小，在插入完成后移动到下一位，等待下一次的比较
        }
        else
        {
            pc->next=pb;
            pc=pb;
            pb=pb->next;
        }
    } 
    
    //比较完之后肯定还有剩余的元素，需要把剩余的元素插入到链表中
    if(pa)
    {
        pc->next=pa;
    }
    if(pb)
    {
        pc->next=pb;
    }

    //也可以用简洁的一句话实现，使用三目运算符
    // pc->next=pa?pa:pb;

    //对于链表来说，合并之后不要忘记释放节点，使得空间利用效率变高
    free(lb);
}

//打印
void printlist(linklist l)
{
    lnode *p;
    p=l->next;//指向首元节点
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
}

int main()
{
    linklist la,lb,lc;
    listinit(la);
    listinit(lb);
    printlist(la);
    printf("\n");
    printlist(lb);
    printf("\n");
    mergelist(la,lb,lc);
    printf("\n");
    printf("mergelist below\n");
    printlist(lc); //需要打印lc查看合并结果
}