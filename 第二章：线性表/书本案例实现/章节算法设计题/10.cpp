/*

题目
已知长度为n的线性表A采用顺序存储结构，实际一个时间复杂度为O（n），空间复杂度为O（1）的算法，
该算法可删除所有值为item的数据元素


思路：通过对元素重新赋值实现删除操作;  弊端：元素的原始顺序全部被改变

反思（对比原来的删除操作）：

正常删除操作的顺序在删除后面的元素的顺序不变，是整体元素的顺序统一加或者减，
但是本题的删除思想每一个元素的顺序有随机被赋值的可能性
*/

#include<stdio.h>
#include<stdlib.h>

#define ok 1
#define error 0
#define overflow -1
#define maxsize 100

typedef int status;
typedef int elemtype;

typedef struct
{
    elemtype data[maxsize];//使用静态数组，降低代码的复杂性
    int length;
}sqlist;

//初始化+录入值
status listinit(sqlist &l)
{
    l.length=0;
    int n;
    printf("how many data do you want yo input:");
    scanf("%d",&n);

    //做一个小优化，如果是非法输入，如何处理？
    if(!scanf("%d",&n))
    {
        //getchar()函数返回的是一个整数值（通常是读取字符的 ASCII 码值），而不是一个字符串
        //你不能将其与"\n"（这是一个字符串）进行比较。正确的做法是将其与换行符的 ASCII 码值'\n'进行比较。
        //所以，while (getchar() != '\n');才是正确的写法
        while(getchar()!='\n');
        printf("invalid input.please input again\n");
    }
    if(n>100)
    {
        printf("out of range,fail to input data\n");
        return overflow;
    }
    printf("\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&l.data[i]);
    }
    printf("\n");
    l.length=n;
    printf("the list is below");
    for(int i=0;i<n;i++)
    {
        printf("%d ",l.data[i]);
    }
    return ok;
}

//删除操作（如果值是item，就删除）
status listdelete(sqlist &l,int item)
{
    int k=0;//记录值不是item的元素，便于后期重新为元素赋值
    for(int i=0;i<l.length;i++)
    {
        if(l.data[i]!=item)
        {
            //把原列表当作空表，遍历列表中的每一个元素，如果值不是item，就从头开始为列表中的每一个元素位置赋值
            l.data[k]=l.data[i];
            k+=1;

            //懒人不讨好写法：  l.data[k++]=l.data[i];   k++：先用后加，在下标为k的地方赋值后，k再自增
        }
    }
    l.length=k; //最后别忘记更新顺序表的长度
    return ok;
}


int main()
{
    sqlist l;
    int item;
    listinit(l);
    printf("please input a element you want to delete in this data:");
    scanf("%d",&item);
    listdelete(l,item);
    printf("the list after delete is below:\n");
    for(int i=0;i<l.length;i++)
    {   
        printf("%d ",l.data[i]);
    }
}