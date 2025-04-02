/*

区别于链栈，链队需要首元节点

*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef int status;
typedef int elemtype;

#define ok 1
#define error 0
#define overflow -1

// 定义链队
typedef struct qnode
{
    elemtype data;
    struct qnode *next;
} qnode, *queueptr;
typedef struct
{
    queueptr front;
    queueptr rear;
} linkqueue;

// 初始化
status linkqueueinit(linkqueue &q)
{
    q.front = (qnode *)malloc(sizeof(qnode));
    q.front->next = NULL;
    q.rear = q.front;
    if (!q.front)
    {
        printf("fail to init\n");
        return error;
    }
    printf("init success\n");
    printf("\n");
    return ok;
}

// 打印队列
void printqueue(linkqueue q)
{
    qnode *temp;
    if (q.front == NULL || q.front->next == NULL)
    {
        printf("the queue is empty\n");
    }
    temp = q.front->next; // 指向首元节点
    while (temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 入队（由于只能在队尾入队,初始时没有元素，采用后插法）
status enqueue(linkqueue &q, elemtype e)
{
    qnode *p;
    p = (qnode *)malloc(sizeof(qnode));
    p->next = NULL;
    p->data = e;
    q.rear->next = p;
    q.rear = p;
    printf("enqueue success\n");
    printf("\n");
    printf("printqueue below:\n");
    printqueue(q);
    return ok;
}

// 出队
status dequeue(linkqueue &q, elemtype &e)
{
    qnode *p;
    p = q.front->next;
    q.front->next = p->next;
    e = p->data;

    // 易错：如果删除的是最后一个元素的位置，刚好是尾指针指向的位置，此时尾指针就被删除了，需要重新赋值
    if (p == q.rear)
    {
        q.rear = q.front;
    }
    free(p);
    printf("the dequeue data is :%d\n", e);
    printf("dequeue success\n");
    printf("\n");
    return ok;
}

// 获取队列长度
status getlength(linkqueue q)
{
    int j = 0;
    qnode *p;
    p = q.front->next;
    while (p)
    {
        p = p->next;
        j += 1;
    }
    printf("the length is :%d\n", j);
    printf("\n");
    return ok;
}

// 获取队头元素
status getheaddata(linkqueue q)
{
    if (q.front != q.rear)
    {
        printf("the headdata is :%d\n", q.front->next->data);
    }
    printf("\n");
    return ok;
}

// 判断是否为空
status isempty(linkqueue q)
{
    if (q.front == q.rear)
    {
        printf("the linkqueue is empty\n");
        return ok;
    }
    else
    {
        printf("the linkqueue is not empty\n");
        return error;
    }
}

// 销毁
status queuedestroy(linkqueue &q)
{
    qnode *p;
    // 用p临时保存下一节点，可以把 q.front 看成是前驱指针，没移动一次删除所指节点，然后重新赋值
    while (q.front)
    {
        p = q.front->next;
        free(q.front);
        q.front = p;
    }
    printf("destroy success\n");
    printf("\n");
    return ok;
}

// 清屏
void clear()
{
    system("cls");
    printf("1.inkqueueuinit\n");
    printf("2.enqueue\n");
    printf("3.dequeue\n");
    printf("4.getlength\n");
    printf("5.getheaddata\n");
    printf("6.isempty\n");
    printf("7.queuedestroy\n");
    printf("8.printqueue\n");
    printf("9.clear\n");
    printf("0.exit\n");
    printf("\n");
}

int main()
{
    printf("1.inkqueueuinit\n");
    printf("2.enqueue\n");
    printf("3.dequeue\n");
    printf("4.getlength\n");
    printf("5.getheaddata\n");
    printf("6.isempty\n");
    printf("7.queuedestroy\n");
    printf("8.printqueue\n");
    printf("9.clear\n");
    printf("0.exit\n");
    printf("\n");

    int choose;
    int e, e1;
    linkqueue q;

    while (1)
    {
        printf("please input the function you want:");
        if (scanf("%d", &choose) != 1)
        {
            while (getchar() != '\n')
            {
                ;
            }
            printf("invalid input,please input again\n");
            continue; // 无效输入，这一次循环暂停，进入下一次循环
        }

        switch (choose)
        {
        case 1:
            linkqueueinit(q);
            printf("\n");
            break;
        case 2:
            printf("input the data you want to enqueue:");
            scanf("%d", &e);
            enqueue(q, e);
            printf("\n");
            break;
        case 3:
            dequeue(q, e1);
            printf("\n");
            break;
        case 4:
            getlength(q);
            printf("\n");
            break;
        case 5:
            getheaddata(q);
            printf("\n");
            break;
        case 6:
            isempty(q);
            printf("\n");
            break;
        case 7:
            queuedestroy(q);
            printf("\n");
            break;
        case 8:
            printqueue(q);
            printf("\n");
            break;
        case 9:
            clear();
            break;
        case 0:
            return 0;
            break;
        }
    }
}