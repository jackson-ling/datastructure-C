#include<stdio.h>
#include<stdlib.h>

#define maxsize 100
#define OK 1
#define ERROR 0
#define OVERFLOW -1 //表示溢出。可用于内存分配的场景


typedef int elemtype;
typedef int status;

//顺序表的定义
typedef struct 
{
    elemtype *data;
    int length;
}sqlist;

//顺序表的初始化
status sqlistinit(sqlist &l)
{
    l.data=(elemtype *)malloc(sizeof(elemtype)*maxsize);
    //空间有可能分配失败，这里做一个判断
    if(!l.data)
    {
        return OVERFLOW;
    }
    l.length=0;
    return OK;
}

//顺序表的取值(输入需要查找的位置，返回对应位置的元素)
//操作结果通过e返回，在主函数中需要定义e，声明e的类型，之后函数传参传e就行，通过打印e的值即可看到操作结果
status getdata(sqlist &l,int i,elemtype &e)
{
    //判断查找位置是否合理
    if(i<1||i>l.length)
    {
        return ERROR;
    }
    else
    {
        e=l.data[i-1];
    }
    return OK;
}

//顺序表的查找（输入需要查找的元素，返回元素的位置）
status finddata(sqlist l,elemtype e)
{
    for(int i=0;i<l.length;i++)
    {
        if(l.data[i]==e)
        {
            return i+1;  //数组下标和实际的物理位置在数值上相差1
        }
    }
    return OK;
}

//顺序表的插入(录入插入的位置和元素)
status listiinsert (sqlist&l,int i,elemtype e)
{
    //首先判断能否插入，插入的位置是否合理
    if(i<1||i>l.length+1)
    {
        return ERROR;
    }
    if(l.length==maxsize)
    {
        return ERROR;
    }
    for(int j=l.length-1;j>=i-1;j--) //直到把把第i个位置（下标索引是i-1）的元素往后挪，空出位置才可以插入
    {
        l.data[j+1]=l.data[j];
    }
    l.length++;
    return OK;
}

//顺序表的删除(录入需要删除的位置)
status deletedata(sqlist &l,int i)
{
    //判断删除的位置是否合理
    if(i<1||i>l.length)
    {
        return ERROR;
    }
    //删除第i个元素（下标是i-1），只需要找到他后面的元素，依次把后面的元素往前移动即可，所以起始位置是i（需要删除元素的后面那个元素）

    for(int j=i;j<=l.length-1;j++)
    {
        l.data[j-1]=l.data[j];
    }
    l.length--;
    return OK;
}
    
//获取顺序表的长度
status getlength(sqlist l)
{
    return l.length;
}

//顺序表的清空(函数没有返回值，使用void类型)
void clearlist(sqlist &l)//表本身的长度发生变化，需要加上&
{
    l.length=0;
}

//顺序表的摧毁(函数没有返回值，使用void类型)
void destroylist(sqlist &l)//摧毁是对顺序表本身的操作，需要加上&
{
    //摧毁的前提是顺序表存在，即已经分配了空间
    if(l.data)
    {
        free(l.data);
    }
}

//判断顺序表是否为空
// (这里是— —“是否”，需要加上else语句形成if - else语句结构进行判断)
status isempty(sqlist l)
{
    if(l.length==0)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

