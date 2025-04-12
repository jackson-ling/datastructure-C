#include <stdio.h>
#include <stdlib.h>

#define ok 1
#define error 0
#define overflows -1

typedef int status;
typedef int elemtype;

typedef struct lnode
{
    elemtype data;
    struct lnode *next;
} lnode, *linklist;

status listinit(linklist *l)
{
    *l = (lnode *)malloc(sizeof(lnode));
    (*l)->next = NULL;
    if (!*l)
    {
        printf("fail to init\n");
        return overflows;
    }
    printf("init success\n");
    printf("\n");
    lnode *q;
    q = *l;
    int n;
    printf("how many data do you want to input:");
    scanf("%d", &n);
    printf("\n");
    printf("input data:");
    for (int i = 0; i < n; i++)
    {
        lnode *p;
        p = (lnode *)malloc(sizeof(lnode));
        p->next = NULL;
        scanf("%d", &p->data);
        q->next = p;
        q = p;
    }
    printf("\n");
    return ok;
}

status mergelist(linklist *la, linklist *lb, linklist *lc)
{
    lnode *pa, *pb, *pc;
    *lc = (lnode *)malloc(sizeof(lnode)); // Create an empty head node for lc
    (*lc)->next = NULL;                   // Start with an empty list
    pc = *lc;                             // pc points to the tail of the merged list

    pa = (*la)->next; // Start from the first node of la
    pb = (*lb)->next; // Start from the first node of lb

    // Merge the two lists into lc (in descending order)
    while (pa && pb)
    {
        if (pa->data > pb->data)
        {
            pc->next = pa; // Insert pa into the merged list
            pa = pa->next; // Move pa to the next node
        }
        else if (pb->data > pa->data)
        {
            pc->next = pb; // Insert pb into the merged list
            pb = pb->next; // Move pb to the next node
        }
        else
        {
            pc->next = pa; // Insert pa (or pb, since they are equal) into the merged list
            pa = pa->next; // Move pa to the next node
            pb = pb->next; // Move pb to the next node
        }
        pc = pc->next; // Move pc to the last node in the merged list
    }

    // If there are remaining nodes in either la or lb, add them to lc
    while (pa)
    {
        pc->next = pa;
        pa = pa->next;
        pc = pc->next;
    }

    while (pb)
    {
        pc->next = pb;
        pb = pb->next;
        pc = pc->next;
    }

    // Print the merged result
    lnode *print = (*lc)->next;
    printf("merge result :");
    while (print)
    {
        printf("%d ", print->data);
        print = print->next;
    }
    printf("\n");

    return ok;
}

int main()
{
    lnode *la, *lb, *lc;
    printf("la init\n");
    printf("\n");
    listinit(&la); // Initialize la
    printf("\n");
    printf("lb init\n");
    printf("\n");
    listinit(&lb); // Initialize lb
    printf("\n");
    mergelist(&la, &lb, &lc); // Merge la and lb into lc
    printf("\n");
}
