#include <stdio.h>
#include <string.h>
/*
注意：该算法返回的是字符串匹配段中第一个字符的位置，这个字符往后移动字符串长度个单位，这些字符是一一匹配的

该算法缺点：时间复杂度是 O(n*m)，时间效率较低，可以使用 KMP 算法  将时间复杂度降低至  O(n+m)


思想：暴力枚举

注意点：回溯的表达式（i-j+2），可以理解为（i-j+1）+1
（1）括号内的加一是表示回到第一个位置，原本计算的元素之间的间隙，例如四个元素三个间隙，实际的位置应该加一才是第四个位置
（2）括号外的加一表示回溯上一次的初始位置的下一个位置

字串位置：字符串中第一个字符在主串中的位置

例如：
主串：beijing
字串：jing

则字串在主串中的位置是  4


串的存储方式注意点：字符窜都是从下标为一的位置开始存储的，下标为0的位置限制不用
*/

// 首先定义串

#define maxsize 100
#define ok 1
#define error 0

typedef struct
{
    char arr[maxsize + 1];
    int length;
} sstring; // 表示顺序串

int index_BF(sstring a, sstring b, int position) // 定义position，可以自行选择初始比较位置
{
    // 注意：默认a是主串，b是字串，a的长度大于b写的算法

    // 从初始化比较的位置
    int i = position;
    int j = 1;
    while (i <= a.length && j <= b.length)
    {
        // 如果相同，就往后移动，继续逐个比较
        if (a.arr[i] == b.arr[j])
        {
            i++;
            j++;
        }
        // 如果不相等，主串中的  i  就回溯，同时 j 回到初始位置，继续下一轮的逐个比较
        else
        {
            i = i - j + 2;
            j = 1;
        }
    }

    // 如果匹配成功，就返回匹配成功段的第一个字符的位置
    if (j > b.length)
    {
        printf("match successful\n");
        printf("the positon is :%d\n", i - b.length);
        return ok;
    }
    // 如果没有匹配成功，，则返回假
    else
    {
        printf("fail to match\n");
        return error;
    }
}

// 写一个初始化字符窜的函数
int stringinit(sstring &s)
{
    printf("please input the string:");
    // 易错：由于是从下标为一的位置开始存储，所以这里录入的时候也应该从下标为一的位置开始录入
    scanf("%s", s.arr + 1);
    // 易错：同理是一样的问题，从下标为1的位置开始往后统计字符
    s.length = strlen(s.arr + 1);
    printf("the string's length which you have input is : %d\n", s.length);
    printf("\n");
    printf("input success\n");
    printf("\n");
    return ok;
}

int main()
{
    int position = 1; // 初始化默认从主串的第一个字符开始比较
    sstring a, b;
    stringinit(a);
    stringinit(b);
    index_BF(a, b, position);
}
