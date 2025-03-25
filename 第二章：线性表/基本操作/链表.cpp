
#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef int elemtype;
typedef int status;

//定义链表
typedef struct lnode
{
    elemtype data;//注意这里不需要指针，书上原始描述是存储一个数据
    struct lnode *next;//指针域（头节点的next域指向下一个节点的地址）
}lnode,*linklist;


/*
 * 指针变量的定义规范说明
 * 1.如果定义linklist p：代表为链表l的— —“头指针”
 * 2.如果定义lnode *p：代表指向某个节点的指针
*/


//用头指针指向头节点，用头指针命名链表

//初始化链表
status listinit(linklist &l)
{
    l=(lnode*)malloc(sizeof(lnode));//注意这里是强转成——lnode——结构体类型
    //优化1：内存分配失败的判断
    if(!l)
    {
        return OVERFLOW;
    }
    l->next=NULL;
    l->data=0;//优化2：初始化数据域，将其置空
    return OK;
}


//链表的取值
status getdata(linklist &l,int i,elemtype &e)
{
    lnode *p;
    int j;
    p=l->next;
    j=1;
    while(p&&j<i)
    {
        p=p->next;
        j++;
    }
    //逻辑:由于循环的出现导致了两种可能的情况，这里需要判断
    if(!p||j>i)
    {
        return ERROR;
    }
    e=p->data;
    return OK;
}


//链表的查找
status locatdata(linklist l,elemtype e)
{
    lnode *p;
    int j;
    p=l->next;
    j=1;
    while(p&&p->data!=e)
    {
        p=p->next;
        j++;
    }
    //书上返回的是地址，这里优化一下，返回元素的位置
    if(p)
    {
        return j;
    }
    else
    {
        return ERROR;
    }
}

//链表的插入
status listinsert(linklist l,int i,elemtype e)
{
    lnode *p;
    lnode *s;
    int j;
    p=l;//注意：插入可以在首元节点之后插入，所以开始的时候不指向首元节点，而是指向头节点
    j=0;
    //先找到第i-1个节点
    while(p&&j<i-1)
    {
        p=p->next;
        j++;
    }
    //由于循环，会产生一些情况，这里需要判断
    if(!p&&j>i-1)
    {
        return ERROR;
    }
    s=(lnode*)malloc(sizeof(lnode));
    s->data=e;
    //指针的修改顺序：先后后前（对于新节点s而言）
    s->next=p->next;
    p->next=s;
    return OK;
}


//链表的删除
status listdelete(linklist l,int i)
{
    lnode *p;
    lnode *q;//引入一个新的结构体指针指向需要删除的元素，便于释放空间
    int j;
    j=1;
    p=l->next;//初始指向首元节点，头节点不能删除

    //同样是先找到第i-1个元素
    while(p&&j<i-1)
    {
        p=p->next;
        j++;
    }
    //同理是循环的原因，加一个判断
    if(!p||j>i-1)
    {
        return ERROR;
    }
    //接着修改指针
    q=p->next;//让q指向需要删除的元素，原先p是指向第i-1个元素，需要删除的是第i个元素
    p->next=q->next;//让p指向下一个的节点变成第i+1个元素，这个元素的地址存储在第i个节点的指针域里面
    free(q);
    return OK;
}


//求链表的长度
status listlength(linklist l)
{
    lnode *p;
    int j;
    p=l->next;//p指向首元节点，就是第一个元素
    j=0;//最开始没有元素
    while(p)
    {
        p=p->next;
        j++;
    }
    return j;
}

//判断链表是否非空
status isempty(linklist l)
{
    if(l->next)
    {
        return ERROR;//如果不为空就返回ERROR
    }
    else
    {
        return OK;//如果为空就返回OK
    }
}

//清空链表(没掌握的，思路比较新颖，本质是逐个释放元素的存储空间)
status clearlist(linklist &l) {
    lnode *p;
    lnode *q;
    p = l->next;//p指向首元节点，即第一个元素

    //理解：p，q两个指针同时移动，p在前面，如果p都为空，q必定为空，此时q就没有移动的必要，循环借宿
    while (p) {
        q = p->next;//引入q，指向p当前所指元素的下一个元素
        free(p);//释放p所指元素的空间
        p = q;//p移动到q的位置，下一次循环开始，q又继续移动到p新指向元素的下辖一个元素，依次循环
    }
    //易错：元素存储空间释放完之后还需要把头节点的指针与置空
    l->next = NULL;
    return OK;
}


//链表的摧毁(区别于清空，摧毁是连头节点都需要删除)
status destroylist(linklist &l)
{
    lnode *p;//同理引入一个新的指针存储元素以便释放空间
    while(l)//只要头指针不为空，就一直删除
    {
        p=l;
        l=l->next;
        free(p);
    }
    return OK;

    //理解：头指针指向的是一段空间，如果头节点都不存在了，头指针也就没有明确的指向，
    //     即链表不存在（因为单链表由头指针唯一确定，通过头指针指向头节点来初始化一个链表）
}


//单链表的创建（注意：由于是链表的创立，不需要返回值，用void类型）

//头插法（本质就是插入算法）
void headinsert(linklist &l,int n)
{
    lnode *p;
    l=(lnode*)malloc(sizeof(lnode));
    l->next=NULL;
    for(int i=0;i<n;i++)
    {
        p=(lnode *)malloc(sizeof(lnode));
        scanf("%d",&(p->data));
        p->next=l->next;
        l->next=p;
    }
}


//后插法(引入一个新的指针r，插入一个元素就移动)
void tailinsert(linklist &l,int n)
{
    lnode *r;
    lnode *p;
    //首先生成头节点
    l=(lnode *)malloc(sizeof(lnode));
    l->next=NULL;
    r=l;//初始没有元素，指向头节点
    for(int i=0;i<n;i++)
    {
        p=(lnode *)malloc(sizeof(lnode));
        scanf("%d",&(p->data));
        p->next=NULL;//指针域需要置空，后面需要接入元素
        r->next=p;
        r=p;
    }




}




