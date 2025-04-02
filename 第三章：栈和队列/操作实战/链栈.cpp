#include <stdio.h>
#include <stdlib.h>

/*

区别于顺序栈：链栈的头指针直接指向栈顶元素，而不是在栈顶元素的上方，同时不需要头节点

*/

#define ok 1
#define error 0
#define overflow -1

typedef int status;
typedef int elemtype;

// 定义链栈
typedef struct stacknode
{
    elemtype data;
    struct stacknode *next;
} stacknode, *linkstack;

// 链栈的初始化
status stackinit(linkstack &s)
{
    s = NULL;
    printf("init success\n");
    return ok;
}

// 打印栈的元素
void printstack(linkstack s)
{
    while (s)
    {
        printf("%d ", s->data);
        s = s->next;
    }
    printf("\n");
}

// 入栈
status pushstack(linkstack &s, elemtype e)
{
    stacknode *p;
    p = (stacknode *)malloc(sizeof(stacknode));
    p->data = e;
    p->next = s;
    s = p;
    return ok;
}

// 出栈
status popstack(linkstack &s, elemtype &e)
{
    stacknode *p;
    if (s == NULL)
    {
        printf("no data in stack,fail to popstack\n");
        return error;
    }
    e = s->data;
    p = s;
    s = s->next;
    free(p);
    printf("the popstack data is %d", e);
    return ok;
}

// 取栈顶元素
status getpop(linkstack s)
{
    if (s == NULL)
    {
        printf("no data in it,fail to popdata\n");
        return error;
    }
    printf("the popdata is : %d", s->data);
    return ok;
}

// 判断是否为空
status isempty(linkstack s)
{
    if (s == NULL)
    {
        printf("the stack is empty\n");
        return error;
    }
    else
    {
        printf("the stack isn't empty\n");
    }
    return ok;
}

// 统计元素个数
status getlength(linkstack s)
{
    int j = 0;
    while (s)
    {
        s = s->next;
        j++;
    }
    printf("the length is %d now\n", j);
    return ok;
}

int main()
{
    int choose, e, n;
    stacknode *s;
    printf("1.stackinit\n");
    printf("2.pushstack\n");
    printf("3.popstack\n");
    printf("4.getpop\n");
    printf("5.isempty\n");
    printf("6.printstack\n");
    printf("7.getlength\n");
    printf("0.exit\n");
    printf("--------------------------------------------------------------------------------------\n");
    while (1)
    {
        printf("please choose the fucntion you want:");
        if (!scanf("%d", &choose))
        {
            while (getchar() != '\n')
                ;
            printf("invalid input,please input again\n");
            continue;
        }
        switch (choose)
        {
        case 1:
            stackinit(s);
            printf("\n");
            break;
        case 2:
            printf("how many data you want to push this time:");
            scanf("%d", &n);
            printf("\n");
            printf("input the data you want to push:");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &e);
                pushstack(s, e);
            }
            printf("the stack is below:\n");
            printstack(s);
            printf("\n");
            break;
        case 3:
            popstack(s, e);
            printf("\n");
            break;
        case 4:
            getpop(s);
            printf("\n");
            break;
        case 5:
            isempty(s);
            printf("\n");
            break;
        case 6:
            printstack(s);
            printf("\n");
            break;
        case 7:
            getlength(s);
            printf("\n");
            break;
        case 0:
            return 0;
        }
    }
}