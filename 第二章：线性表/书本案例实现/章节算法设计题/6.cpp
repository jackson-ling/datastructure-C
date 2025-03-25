/*

题目：通过一趟遍历确定长度为n的单链表中值最大的节点

*/

#include<stdio.h>
#include<stdlib.h>

typedef int status;
typedef int elemtype;

typedef struct lnode
{
    elemtype data;
    struct lnode *next;
}lnode,*linklist;

//初始化顺序表并录入元素
status listinit(linklist &l)
{
    
}