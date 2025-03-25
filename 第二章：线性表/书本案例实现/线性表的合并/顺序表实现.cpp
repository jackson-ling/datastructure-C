/*

    案例实现：实现求两个集合的并集
    思路：首先获取两个集合的长度，遍历两个集合，如果集合B的元素在集合A里面没有就执行插入操作，更新集合的长度
    A=（7，5，3，11）
    B=（2，6，3）

    并集集合C的结果；C=（7，5，3，11，2，6）

*/

//说明：虽然打印说明可以呈现函数执行的状态，但是如果没有返回值就会出现诸多问题。例如在if的判断中会出错


#include<stdio.h>
#include<stdlib.h>

#define maxsize 100
#define ok 1
#define error 0
#define overflow -1

typedef int elemtype;
typedef int status;


//定义一个顺序表
typedef struct
{   
    elemtype *data;//需要把值通过参数返回，这里使用指针类型，便于使用  &---引用
    int length;
}sqlist;


//初始化
status listinit(sqlist &l)
{
    l.data=(elemtype*)malloc(sizeof(elemtype)*maxsize);
    if(!l.data)
    {
        printf("fail to init\n");
        return overflow;
    }
    l.length=0;
    printf("listinit success\n");
    printf("\n");
    return ok;
}

//取值（录入位置返回对应位置的元素）
status getdata(sqlist l,int i,elemtype &e)
{
    if(i<1||i>l.length)
    {
        printf("you input is out of range,fail to getdata\n");
        return error;
    }
    else
    {
        e=l.data[i-1];
    }
    printf("getdata success\n");
    printf("\n");
    return ok;
}

//查找(返回元素的位置)

//返回值尤其重要，在后续的判断中为真还是为假会影响最终的合并结果
status locatedata(sqlist l,elemtype e)
{
    for(int i=0;i<l.length;i++)
    {
        if(l.data[i]==e)
        {
            return i+1;
        }
    }
    return error;//如果遍历完整个列表都没有找到，返回error
    printf("locatedata success\n");
    printf("\n");
    return ok;
}

//插入
status listinsert(sqlist &l,int i,elemtype e)
{
    if(i<1||i>l.length+1)
    {
        printf("the location you want to insert is wrong\n");
        return error;
    }
    for(int j=l.length-1;j>=i-1;j--)
    {
        l.data[j+1]=l.data[j];
    }
    l.data[i-1]=e;
    l.length++;
    return ok;
}

//打印顺序表(打印顺序表不需要有返回值)
void printlist(sqlist l)
{
    for(int i=0;i<l.length;i++)
    {
        printf("%d ",l.data[i]);
    }
    printf("\n");
    printf("printlist success\n");
}


////合并算法实现
void mergelist(sqlist &la,sqlist lb)
{
    int m,n,e;
    m=la.length;
    n=lb.length;
    //遍历lb的元素，如果lb的元素不在la中，就插入到la中
    for(int i=1;i<=n;i++)//特别注意这里的下标问题，结合之前函数的判断
    {
        getdata(lb,i,e);  //这里需要取值函数的原因是遍历的对象是下标，而不像指针可以直接访问某个地址的值
        if(!locatedata(la,e))
        {
            //特别重点易错：++m，先让位置加以（移动到下一个位置）之后再把值传入函数进行插入，否则使用m++会使插入结果出错
            listinsert(la,++m,e);//插入在链表的后面，即l.length+1的位置
        }
    }
    printf("mergelist success\n");
}

int main()
{
    sqlist a;
    sqlist b;
    listinit(a);
    listinit(b);
    printf("how many data do you want to input set a?");
    scanf("%d",&a.length);
    printf("\n");
    printf("please input data in set a:");
    for(int i=0;i<a.length;i++)
    {
        scanf("%d",&a.data[i]);
    }
    printf("input success\n");
    printf("how many data do you want to input set b?");
    scanf("%d",&b.length);
    printf("\n");
    printf("please input data in set b:");
    for(int i=0;i<b.length;i++)
    {
        scanf("%d",&b.data[i]);
    }
    printf("input success\n");
    printf("\n");
    //注意打印是按照数组的长度打印的，不是自己输入一个值，数组的长度需要更新
    printlist(a);
    printf("\n");
    printlist(b);
    printf("\n");
    mergelist(a,b);
    printf("the result of merging below\n");
    printlist(a);

    //申请了空间，最后需要释放
    free(a.data);
    free(b.data);
}