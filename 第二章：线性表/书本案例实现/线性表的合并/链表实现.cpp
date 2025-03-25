#include<stdio.h>
#include<stdlib.h>


/*
本代码花费较长时间的原因————自己的错误点
1.遇到问题着急AI，没有回看代码的逻辑（调试的思想）
2.没有搞懂代码的运行逻辑，本来就是没有找到（fail to locate）才需要插入，但是以为这里出错了，纠结了很久，浪费了很多时间
3.忽略了打印最后的la查看合并结果，同时也出现了fail to locate，就以为是代码哪里出问题了
*/

/*
线性表合并的思路（求并集）

1.首先线性表是无序的，不需要考虑顺序，本质就是求两个集合的并集
2.假设有集合A，B，最后结果并集的结果合并在集合A里面，具体的步骤如下：

    1.遍历B集合中的每一个元素————运用取值函数
    2.保存遍历的数，在A集合中查找————运用查找函数
    3.如果A集合中不存在，就插入到A集合中————运用插入函数

*/



#define error 0
#define ok 1
#define overflow -1

typedef int status;
typedef int elemtype;

//定义链表
typedef struct lnode
{
    elemtype data;
    struct lnode *next;
}lnode,*linklist;

//链表的初始化+录入元素
status listinit(linklist &l)
{
    l=(lnode*)malloc(sizeof(lnode));
    l->next=NULL;
    if(!l)
    {
        printf("fail to init\n");
        printf("\n");
        return overflow;
    }
    lnode *p,*s;
    p=l;
    int n;
    printf("how many data do you want to input? ");
    //使用后插法创建链表，然后对值进行录入
    scanf("%d",&n);
    printf("\n");
    printf("please input data in it:");
    for(int i=0;i<n;i++)
    {
        s=(lnode*)malloc(sizeof(lnode));
        scanf("%d",&s->data);
        s->next=NULL;
        p->next=s;
        p=s;
    }
    return ok;
}

//获取线性表的长度
status getlength(linklist l)
{
    lnode *p;
    p=l->next;
    int j=0;
    while(p)
    {
        p=p->next;
        j++;
    }
    return j;
}

//链表中的取值
status getdata(linklist l,int i,elemtype &e)
{
    lnode *p;
    int j=1;
    p=l->next;
    while(p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i)
    {
        printf("error\n");
        return error;
    }
    e=p->data;
    return ok;
}

//链表的查找
status locatedata(linklist l,elemtype e)
{
    lnode *p;
    p=l->next;
    while(p&&p->data!=e)
    {
        p=p->next;
    }
    if(!p)
    {
        printf("fail to locate\n");
        return error;
    }
    return ok;
}

//链表的插入(注意：插入可以在头节点后面插入，初始时指向头节点)
status listinsert(linklist &l,int i,elemtype e)
{
    lnode *p,*s;
    p=l;
    int j=0;
    while(p&&j<i-1)
    {
        p=p->next;
        j++;
    }
    s=(lnode *)malloc(sizeof(lnode));
    s->next=NULL;
    s->data=e;

    //注意：先改变后继指针，再改变前驱指针

    s->next=p->next;
    p->next=s;
    return ok;
}


//合并操作

//同理采用链表合并中的思想：不需要新生成一个链表，用新的头指针指向已有的头节点即可

status mergelist(linklist &la,linklist &lb)
{
    int m,n;
    int e;
    m=getlength(la);
    n=getlength(lb);
    //接着遍历链表lb，取出每一个值，在链表la中查找，如果没有，就插入
    lnode *p;
    p=lb->next;

     //注意: 不同于顺序表，j<n这个条件在顺序表中是表示元素下标，
     //      但在链表中表示的是第几个元素，遍历完之后可能会有j>n（a的元素少，b的元素多）
     //      这个时候就会导致一些元素丢失
    while(p)
    {
        // getdata(lb,j,e);   注意点：区别于顺序表，利用指针一一遍历，这样可以直接取出某个节点的值，
        //                           可以不用单独写取值函数，然而再顺序表中遍历的对象是数组的下标

        e=p->data; //遍历每一个节点，取出该节点的值，如果再la中不存在，就插入到la的后面
        if(!locatedata(la, e))
        {
            listinsert(la,++m,e);
        }
        p=p->next;
    }
    return ok;
}

void printlist(linklist l)
{
    lnode *p;
    p=l->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

//释放节点需要把每个一节点都释放掉，而不是像顺序表申请的一段连续的空间，直接释放就行
//即链表的摧毁
void freelist(linklist l)
{
    lnode *p,*q;
    p=l->next;
    while(p)
    {
        q=p;
        p=p->next;
        free(q);
    }
    free(l);
}
int main()
{
    linklist la,lb;
    listinit(la);
    printlist(la);
    printf("\n");
    listinit(lb);
    printlist(lb);
    printf("\n");
    mergelist(la,lb);
    printf("\n");
    printf("mergelist below\n");
    printlist(la);
    
    //注意：链表的操作最后要释放内存，是需要释放每一个节点的内存
    freelist(la);
    freelist(lb);
}
