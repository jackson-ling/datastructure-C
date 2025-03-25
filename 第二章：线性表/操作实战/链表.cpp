#include<stdio.h>
#include<stdlib.h>

//对链表的理解还不够深，抓住核心：指针

typedef int elemtype;
typedef int status;

//说明：如果是指向某个节点的指针就使用 lnode *p;如果是指向下一个节点的指针直接使用linklist即可

//定义一个链表
typedef struct lnode   //易错：这里要有lnode，区别于顺序表，这里是结构体类型有所不同，声明这里是一个结构体的类型
{
    elemtype data;//数据域
    struct lnode *next;//指针域，存储的是下一个节点的地址，所以用next
}londe,*linklist;

//初始化一个链表（由一个头指针指向头节点，头指针是核心，所以这里是结构体指针类型）
status listinit(linklist &l)
{
    int choose,j=0,n;
    lnode *p,*q;
    l=(lnode*)malloc(sizeof(lnode));
    if(!l)
    {
        printf("fail to init \n");
    }
    else
    {
        printf("listinit success\n");
    }
    l->next=NULL;
    p=l;
    printf("\n");
    printf("do you want to put some data in it? yes:input 1;no:input 0\n");
    scanf("%d",&choose);
    if(choose==1)
    {
        printf("how many data do want to input:");
        scanf("%d",&n);
        printf("input data:");
        for(int i=0;i<n;i++)
        {
            lnode *s;
            s=(lnode *)malloc(sizeof(lnode));
            scanf("%d",&(s->data));
            s->next=NULL;
            p->next=s;
            p=s;
            j++;
            if(n==j)
            {
                break;
            }
        }
        printf("input success\n");
        printf("\n");
        printf("printlist below\n");
        q=l->next;
        while(q)
        {
            printf("%d ",q->data);
            q=q->next;
        }
        printf("\n");
    }
    else if(choose==0)
    {
        ;//什么也不做，用;占位，类似于python中的pass
    }
    printf("-------------------------------------------------------------------------------------------------\n");
}

//链表的取值
status getdata(linklist l,int i)
{
    int j=1;//由于链表无法像顺序表那样随机存取，链表是顺序存储结构，所以需要一个计数器来记录
    lnode *p;
    int e;
    p=l->next;
    while(p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i)
    {
        printf("the data can't find in this linklist\n");
        while (getchar() != '\n'); 
    }
    e=p->data;
    printf("the data you want to get is %d\n",e);
    printf("getdata success\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}


//链表的查找
status locatedata(linklist l,elemtype e)
{
    lnode *p;
    int j=1;
    p=l->next;
    while(p&&p->data!=e)
    {
        p=p->next;
        j++;
    }
    if(!p)
    {
        printf("the data you find is not in the linklsit\n");
    }
    else
    {
        printf("the location of the data you want to find is %d\n",j);
    }
    printf("locatedata success\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}


//插入-----------有问题
status listinsert(linklist &l,int i,elemtype e)
{
    lnode *s;//生成一个新的节点存储插入的元素,同理是用指针指向这个节点
    lnode *p;
    int j=0;
    p=l;//由于插入可以在头节点后面插入，所以开始的时候头指针指向头节点
    while(p&&j<i-1) //思路是先找到第i-1个节点（操作本质：相当于取出第i-1个元素但是取出来）
    {
        p=p->next;
        j++;
    }
    if(!p||j>i-1)
    {
        printf("fail to insert\n");
    }
    s=(lnode*)malloc(sizeof(lnode));
    s->data=e;//给新节点的数据域赋值
    //修改指针：先后后前
    s->next=p->next;
    p->next=s;
    printf("insert success\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}

//删除
status listdelete(linklist &l,int i)
{
    lnode *q;//用一个新的指针指向需要删除的节点，方便释放节点
    lnode *p;
    int j=1;//删除的对象是元素，不能删除首元节点，初始时指向首元节点
    p=l->next;
    while(p&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(!p&&j>i-1)
    {
        printf("faile to delete\n");
    }
    q=p->next;
    p->next=q->next;
    free(q);
    printf("the data you delete is %d\n",q->data);
    printf("now the linklist is:");
    while(p)
    {
        p=p->next;
        printf("%d ",p->data);
    }
    printf("\n");
    printf("list delete success\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}


//求链表的长度(这里不包含头节点，对象是元素的个数)
status getlength(linklist l)
{
    lnode *p;
    int j=1;
    p=l->next;
    while(p)
    {
        p=p->next;
        j++;
    }
    printf("the linklist's length is %d\n",j);
    printf("getlength success\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}

//判断链表是否为空
status isempty(linklist l)
{
    lnode *p,*q;
    int j;
    p=l;
    q=l->next;
    j=1;
    while(q)
    {
        q=q->next;
        j++;
    }
    if(!p->next==NULL)
    {
        printf("the linklist is not empty,there is %d data in it\n",j);
    }
    else
    {
        printf("the linklist is empty\n");
    }
    printf("isempty success\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}

//链表的清空(从首元节点开始组个释放元素)

//不会的地方：没有想到引入两个指针变量，理解还不够深，只要是需要释放节点都需要引入新的指针变量
status clearlist(linklist &l)
{
    lnode *p,*q;//让p指针在q指针的前面
    p=l->next;
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    l->next=NULL;//这里也易错：清空元素后需要对头节点的指针域置空
    isempty(l);
    printf("clearlist success\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}


//链表的摧毁(区别于清空，连头节点都需要删除，这个时候引入的新指针变量就是p)
status destroylist(linklist &l)
{
    lnode *p;
    while(l)
    {
        p=l;//初始时指向头节点
        l=l->next;
        free(l);
    }
    isempty(l);
    printf("destroylist success\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}

//打印链表的元素
void printlist(linklist l)
{
    lnode *p;
    p=l->next;
    while(p)
    {
        p=p->next;
        printf("%d ",p->data);
    }
    printf("printlist success\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}

//链表的创建—— ——后插法
status creatlist_tail(linklist &l)
{
    lnode *p,*s;
    int n,elem;
    //生成头节点
    l=(lnode *)malloc(sizeof(lnode));
    l->next=NULL;
    printf("how many lnode do you want to creat:");
    scanf("%d",&n);
    p=l;
    printf("please input some data you want to put in this lnode below\n");
    for(int i=0;i<n;i++)
    {
        s=(lnode *)malloc(sizeof(lnode));
        s->next=NULL;
        scanf("%d",&elem);
        p->next=s;
        p=s;
    }
    printf("creatlist_tail success\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}

//链表的创建—— ——前插法
status creatlist_head(linklist &l)
{
    lnode *p;
    int n,elem;
    //生成头节点
    l=(lnode *)malloc(sizeof(lnode));
    l->next=NULL;
    printf("how many lnode do you want to creat:");
    scanf("%d",&n);
    printf("\n");
    printf("please input some data you want to put in this lnode below\n");
    for(int i=0;i<n;i++)
    {
        p=(lnode *)malloc(sizeof(lnode));
        p->next=l->next;
        l->next=p;
        scanf("%d",&elem);
    }
    printf("-------------------------------------------------------------------------------------------------\n");
}


//循环链表

//双向链表

int main()
{
    linklist l;//定义一个头指针，单链表由头指针唯一确定
    int location,choose,elem;
    printf("Welcome to use my linklist test system\n");
    printf("\n");
    printf("1.listinit\n");
    printf("2.getdata\n");
    printf("3.locatedata\n");
    printf("4.listinsert\n");
    printf("5.listdelete\n");
    printf("6.getlength\n");
    printf("7.isempty\n");
    printf("8.clearlist\n");
    printf("9.destroylist\n");
    printf("10.printlist\n");
    printf("11.creatlist_head\n");
    printf("12.creatlist_tail\n");
    printf("0.exit\n");
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("plese choose a function:");
    while(1)
    {
        // 核心：输入非法字符，清理输入缓冲区
        if (scanf("%d", &choose) != 1)
        {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a valid number.\n");
            continue;
        }

        scanf("%d",&choose);
        switch(choose)
        {
            case 1:
                printf("\n");
                printf("now the function is listinit\n");
                printf("\n");
                listinit(l);
                printf("plese choose a function:");
                break;
            case 2:
                printf("\n");
                printf("now the function is getdata\n");
                printf("\n");
                printf("input the location you want to get a data:");
                scanf("%d",&location);
                fflush(stdin);
                getdata(l,location);
                printf("plese choose a function:");
                break;
            case 3:
                printf("\n");
                printf("now the function is locatedata\n");
                printf("\n");
                printf("please input a data whose location you want to get:");
                scanf("%d",&elem);
                locatedata(l,elem);
                printf("plese choose a function:");
                break;
            case 4:
                printf("\n");
                printf("now the function is listinsert\n");
                printf("\n");
                printf("please input a location which you want to input a data:");
                scanf("%d",&location);
                printf("the data you want to insert is:");
                scanf("%d",&elem);
                listinsert(l,location,elem);
                printf("now the sqlist is\n");
                printlist(l);
                printf("plese choose a function:");
                break;
            case 5:
                printf("\n");
                printf("now the function is listdelete\n");
                printf("\n");
                printf("please input a location which you want to delete a data:");
                scanf("%d",&location);
                listdelete(l,location);
                printf("now the sqlist is\n");
                printlist(l);
                printf("plese choose a function:");
                break;
            case 6:
                printf("\n");
                printf("now the function is getlength\n");
                printf("\n");
                getlength(l);
                printf("plese choose a function:");
                break;
            case 7:
                printf("\n");
                printf("now the function is isempty\n");
                printf("\n");
                isempty(l);
                printf("plese choose a function:");
                break;
            case 8:
                printf("\n");
                printf("now the function is clearlist\n");
                printf("\n");
                clearlist(l);
                printf("plese choose a function:");
                break;
            case 9:
                printf("\n");
                printf("now the function is destroylist\n");
                printf("\n");
                destroylist(l);
                printf("plese choose a function:");
                break;
            case 10:
                printf("\n");
                printf("now the function is printlist\n");
                printf("\n");
                printlist(l);
                printf("plese choose a function:");  
                break;
            case 11:
                printf("\n");
                printf("now the function is creatlist_head\n");
                printf("\n");
                creatlist_head(l);
                printf("plese choose a function:");  
                break;
            case 12:
                printf("\n");
                printf("now the function is creatlist_head\n");
                creatlist_tail(l);
                printf("plese choose a function:");  
                break;
            case 0:
                printf("\n");
                printf("Thank you for using this sequential list test system!\n\nI'm looking forward to meeting with you next time!\n");
                return 0;  
        }
    }

}