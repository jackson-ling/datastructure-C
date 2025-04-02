/*

栈的特点
（1）后进先出（想象装电池的场景，最后装进去的最先取出来）
（2）由一个base指针和top指针，top指针始终在栈顶元素的上方

思考：为什么要在栈顶元素的上方？
（1）根据数组的特点，下标是从0开始的（s.base视为指向第0个元素），
     top-base就是栈存储的元素，即当前的maxsize
（2）如果在栈顶元素的上方，当每次录入元素的时候就可以直接赋值，不需要移动过多次指针，更方便

区别于顺序表和链表，只能再栈顶进行插入和删除


*/

#include <stdio.h>
#include <stdlib.h>

typedef int status;
typedef int elemtype;

#define ok 1
#define error 0
#define overflow -1

// 定义一个栈
typedef struct
{
    elemtype *base;
    elemtype *top;
    int stacksize; // 记录栈中的元素
} sqstack;

// 打印栈中的元素
void printstack(sqstack s)
{
    int maxsize;
    maxsize = s.top - s.base;
    if (maxsize == 0)
    {
        printf("the stack hava no data\n");
    }
    printf("the stack is:");
    while (s.base != s.top)
    {
        printf("%d ", *s.base);
        s.base++;
    }
    printf("\n");
}

// 栈的初始化+录入元素
status sqstackinit(sqstack &s)
{
    int maxsize, elem, n;
    printf("how large space do you want to init to save data:");
    scanf("%d", &maxsize);

    // 首先分配一段存储空间，用base指针指向这段存储空间
    s.base = (elemtype *)malloc(sizeof(elemtype) * maxsize);
    s.top = s.base;
    s.stacksize = maxsize;

    if (!s.base)
    {
        printf("fail to init\n");
    }
    printf("how many data do you want to input this time :");
    scanf("%d", &n);
    printf("please input data :");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &elem);
        *s.top = elem; // 录入一个元素，栈顶指针上移一个位置
        s.top++;
    }
    printstack(s);
    printf("\n");
    return ok;
}

// 入栈，出战只能在栈顶进行（即只能在栈顶进行插入和删除）

// 入栈
status pushstack(sqstack &s, elemtype e)
{
    int maxsize, temp; // 用一个temp记录当前的元素个数
    // 栈满的判断
    maxsize = s.top - s.base;
    if (maxsize == s.stacksize)
    {
        printf("the stack is full,fail to pushstack\n");
        return error;
    }
    *s.top = e;
    s.top++;
    temp = s.top - s.base;
    printf("now the number of data in it is:%d\n", temp);
    printstack(s);
    return ok;
}

// 出栈
status popstack(sqstack &s)
{
    int elem;
    // 如何判断栈空？根据两个指针和存储元素的特点来判断
    if (s.base == s.top)
    {
        printf("fail to popstack,there have no data in stack\n");
        return error;
    }
    // 注意：栈顶指针在栈顶元素的上方，需要先移动指针指向栈顶元素,这个时候再把栈顶元素保存
    s.top--;
    elem = *s.top; // 注意逻辑，把这个元素赋值给elem
    printf("the popstack data is :%d", elem);
    printf("\n");
    return ok;
}

// 取栈顶元素（易错：栈顶指针始终指向栈顶元素的上方，取栈顶元素注意top指针指向的位置）
status gettop(sqstack s)
{
    // 判断栈空
    if (s.base == s.top)
    {
        printf("fail to getpop,because no data in stack\n");
        return error;
    }
    printf("the pop data is :%d", *(s.top - 1));
    printf("\n");
    return ok;
}

// 判断是否为空
status isempty(sqstack s)
{
    if (s.base == s.top)
    {
        printf("the sqstack is empty\n");
    }
    else
    {
        printf("the data isn't empty\n");
    }
    printf("\n");
    return ok;
}

// 清空栈（就当作栈是空的，此时只需要栈顶指针指向栈底指针）
status clearstack(sqstack &s)
{
    // 清空的前提是栈存在
    if (s.base)
    {
        s.top = s.base;
    }
    s.stacksize = 0;
    printf("clear success\n");
    printf("\n");
    return ok;
}

// 摧毁栈
status destroystack(sqstack &s)
{
    // 摧毁的前提是栈存在
    if (s.base)
    {
        // 栈是如何定义的？使用base指针指向一块申请的空间，如果base指针都不存在了，
        // 这段空间就无法找到，相当于销毁了
        free(s.base);
        s.stacksize = 0;
        s.base = s.top = NULL;
    }
    printf("destroy success\n");
    printf("\n");
    return ok;
}

// 获取当前栈中元素的个数
status getlength(sqstack s)
{
    printf("now the number of data is %d\n", s.top - s.base);
    printf("the stacksize is %d,you can only input %d data after\n", s.stacksize, s.stacksize - (s.top - s.base));
    printf("\n");
    return ok;
}

int main()
{
    int choose;
    sqstack s;
    printf("1.sqstackinit\n");
    printf("2.pushstack\n");
    printf("3.popstack\n");
    printf("4.getpop\n");
    printf("5.isempty\n");
    printf("6.clearstack\n");
    printf("7.destroystack\n");
    printf("8.printstack\n");
    printf("9.getlength\n");
    printf("0.exit\n");
    printf("--------------------------------------------------------------------------------------\n");
    ;
    while (1)
    {
        printf("please choose the fucntion you want:");
        if (!scanf("%d", &choose))
        {
            while (getchar() != '\n')
                ;
            printf("invalid inpput,please input again\n");
            continue;
        }
        switch (choose)
        {
        case 1:
            sqstackinit(s);
            printf("\n");
            break;
        case 2:
            printf("\n");
            printf("Attention!!!\n");
            printf("\n");
            getlength(s);
            if (s.top - s.base == s.stacksize)
            {
                ;
            }
            else
            {
                printf("how many data do you want to input this time:");
                int n, data;
                scanf("%d", &n);
                printf("input the data:");
                for (int i = 0; i < n; i++)
                {
                    scanf("%d", &data);
                    pushstack(s, data);
                }
                printf("\n");
            }
            break;
        case 3:
            popstack(s);
            printf("\n");
            break;
        case 4:
            gettop(s);
            printf("\n");
            break;
        case 5:
            isempty(s);
            printf("\n");
            break;
        case 6:
            clearstack(s);
            printf("\n");
            break;
        case 7:
            destroystack(s);
            printf("\n");
            break;
        case 8:
            printstack(s);
            printf("\n");
            break;
        case 9:
            getlength(s);
            printf("\n");
            break;
        case 0:
            return 0;
        }
    }
}
