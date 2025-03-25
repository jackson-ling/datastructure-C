//易错点一:只要是对顺序表本身操作了，就要使用&

//易错点二：使用switch-case结构需要使用break

//易错点三：有一些操作不需要返回值，函数类型应该是void


//待优化点：如果输入非法字符造成的无限循环的问题


#include<stdio.h>
#include<stdlib.h>

#define maxsize 100

typedef int elemtype;
typedef int status;

//定义一个顺序表

typedef struct
{
    elemtype *data;
    int length;
}sqlist;


//初始化一个顺序表
status listinit(sqlist &l)
{
    l.data=(elemtype *)malloc(sizeof(elemtype)*maxsize);
    if(!l.data)
    {
        printf("space is full,fail to init a space to save data\n");
    }
    l.length=0;
    printf("init success\n");
}

//取值
status getdata(sqlist l,int i)
{
    int e;
    if(i<1||i>l.length)
    {
        printf("the location which you input is wrong\n");
    }
    e=l.data[i-1];
    printf("the data you want to get is %d\n",e);
}

//查找
status locatedata(sqlist l,elemtype e)
{
    int location;
    for(int i=0;i<l.length;i++)
    {
        if(l.data[i]==e)
        {
            location=i+1;
        }
    }
    printf("the data's location which you want to get is %d\n",location);
}

//插入
status listinsert(sqlist &l,int i,elemtype e)
{
    if(i<1||i>l.length+1)
    {
        printf("the location which you want to insert a data is wrong\n");
    }
    for(int j=l.length-1;j>=i-1;j--)
    {
        l.data[j+1]=l.data[j];
    }
    l.data[i-1]=e;
    l.length++;
    printf("insert success\n");
}

//删除
status listdelete(sqlist &l,int i)
{
    if(i<1||i>l.length)
    {
        printf("the location which you want to delete a data is wrong\n");;
    }
    for(int j=i;j<=l.length-1;j++)//从第i+1个元素到最后一个元素都要挪动，注意不要遗漏等号
    {
        l.data[j-1]=l.data[j];
    }
    l.length--;
    if(!l.data[i-1])
    {
        printf("the location not have data in");
    }
    printf("the data you delte is %d",l.data[i-1]);
    printf("delete success\n");
}

//判断是否为空
status isempty(sqlist l)
{
    if(l.length==0)
    {
        printf("the sqlist is empty\n");
    }
    else
    {
        printf("the sqlist is not empty,now there is %d in it!\n",l.length);
    }
}


//求顺序表的长度
status getlength(sqlist l)
{
    printf("the sqlist's legnth is %d\n",l.length);
}

//清空顺序表
void clearlist(sqlist &l)
{
    l.length=0;
    printf("clear success\n");
}

//摧毁顺序表
void destroylist(sqlist &l)
{
    if(l.data)
    {
        free(l.data);
        l.length=0;
    }
    printf("destroy success\n");
}

//打印顺序表
void printlist(sqlist l)
{
    if(l.length==0)
    {
        printf("the list is empty!\n");
    }
    else
    {
        for(int i=0;i<l.length;i++)
        {
            printf("%d ",l.data[i]);
        }
        printf("\n");
    }
}
    



int main()
{       

    int choose,location,elem,n;
    sqlist l;
    
    printf("Welcome to use my sqlist test system\n");
    printf("\n");
    printf("1.listinit\n");
    printf("2.getdata\n");
    printf("3.locatedata\n");
    printf("4.listinsert\n");
    printf("5.listdelte\n");
    printf("6.isempty\n");
    printf("7.getlength\n");
    printf("8.clearlist\n");
    printf("9.destroylist\n");
    printf("10.printlist\n");
    printf("0.exit\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("plese choose a function:");
    while(1)
    {   
        // 核心：输入非法字符，清理输入缓冲区
        if (scanf("%d", &choose) != 1)//表示非法输入，scanf的条件为假
        {
            //getchar()不断从输入缓冲区读取字符，当遇到换行符循环就终止，
            //需要注意的是：先读取字符，再做判断，实际上再循环终止的时候换行符已经被读走了
            //这个时候才发现读取的是换行符，符合条件，循环终止，输入缓冲区被完全清除

            //getchar()函数返回的是一个整数值（通常是读取字符的 ASCII 码值），而不是一个字符串
            //你不能将其与"\n"（这是一个字符串）进行比较。正确的做法是将其与换行符的 ASCII 码值'\n'进行比较。
            //所以，while (getchar() != '\n');才是正确的写法
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
                printf("now you should input some data in it\n");
                printf("How many elements do you want to input this time:");
                scanf("%d",&n);
                printf("please input data:");
                for(int i=0;i<n;i++)
                {
                    scanf("%d",&l.data[i]);
                }
                l.length=n;//易错：不要忘记更新长度
                printf("input success!\n");
                printf("---------------------------------------------------------------------------------------------------------\n");
                printf("plese choose a function:");
                break;
            case 2:
                printf("\n");
                printf("now the function is getdata\n");
                printf("\n");
                printf("please input a location whose data you want to get:");
                scanf("%d",&location);
                getdata(l,location);
                printf("---------------------------------------------------------------------------------------------------------\n");
                printf("plese choose a function:");
                break;
            case 3:
                printf("\n");
                printf("now the function is locatedata\n");
                printf("\n");
                printf("please input a data whose location you want to get:");
                scanf("%d",&elem);
                locatedata(l,elem);
                printf("---------------------------------------------------------------------------------------------------------\n");
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
                printf("---------------------------------------------------------------------------------------------------------\n");
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
                printf("---------------------------------------------------------------------------------------------------------\n");
                printf("plese choose a function:");
                break;
            case 6:
                printf("\n");
                printf("now the function is isempty\n");
                printf("\n");
                isempty(l);
                printf("---------------------------------------------------------------------------------------------------------\n");
                printf("plese choose a function:");
                break;
            case 7:
                printf("\n");
                printf("now the function is getlength\n");
                printf("\n");
                getlength(l);
                printf("---------------------------------------------------------------------------------------------------------\n");
                printf("plese choose a function:");
                break;
            case 8:
                printf("\n");
                printf("now the function is clearlist\n");
                printf("\n");
                clearlist(l);
                printf("---------------------------------------------------------------------------------------------------------\n");
                printf("plese choose a function:");
                break;
            case 9:
                printf("\n");
                printf("now the function is destroylist\n");
                printf("\n");
                destroylist(l);
                printf("---------------------------------------------------------------------------------------------------------\n");
                printf("plese choose a function:");
                break;
            case 10:
                printf("\n");
                printf("now the function is printlist\n");
                printf("\n");
                printlist(l);
                printf("---------------------------------------------------------------------------------------------------------\n");
                printf("plese choose a function:");
                break;
            case 0:
                printf("\n");
                printf("Thank you for using this sequential list test system!\n\nI'm looking forward to meeting with you next time!\n");
                return 0;
            default:
                printf("The number you input is wrong and has no matching function. Please input agian!\n");
                printf("---------------------------------------------------------------------------------------------------------\n");
        }
    }
    
}