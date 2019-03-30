#include <stdio.h>

#define MAXSIZE 100
#define OK 1
#define ERROR 0

typedef char ElemType;
typedef int Status;

typedef struct
{
    ElemType data;
    int cur;
}StaticLinkList[MAXSIZE];

/* 初始化，将链表游标全部赋值 */
Status InitList(StaticLinkList space)
{
    int i;

    for(i=0; i<MAXSIZE-1; ++i)
        space[i].cur = i+1;
    space[MAXSIZE-1].cur = 0;

    return OK;
}

/* 分配空闲节点，返回空闲节点下标 */
int Malloc_SSL(StaticLinkList space)
{
    int i = space[0].cur;

    if(i)
        space[0].cur = space[i].cur;
    return i;
}

/* 回收节点 */
void Free_SSL(StaticLinkList space, int k)
{
    space[k].cur = space[0].cur;    //将备用链表的第一个分量游标赋值给第k个元素的游标
    space[0].cur = k;               //将第k个元素的下标赋值给空闲链表第一个分量的游标
}

/* 获取链表长度 */
int ListLength(StaticLinkList L)
{
    int j,k;    //j表示计数器，k表示第k个元素
    j = 0;

    k = L[MAXSIZE-1].cur;   //k指向第一个元素
    while(k)
    {
        k = L[k].cur;   //k指向下一元素
        ++j;            //元素个数+1
    }
    return j;
}

/* 链表的插入 */
Status ListInsert(StaticLinkList L, int i, ElemType e)
{
    int j,k,l;      //j表示计数器，k表示第k个元素,l表示空闲分量下标
    k = MAXSIZE-1;  //k先指向数组最后分量

    if(i<1 || i>ListLength(L)+1)    return ERROR;
    l = Malloc_SSL(L);
    if(l)
    {
        L[l].data = e;
        for(j=1; j<i; ++j)
            k = L[k].cur;      //k指向第j个元素
        L[l].cur = L[k].cur;   //将第k个元素的的游标赋值给空闲分量的游标
        L[k].cur = l;           //将空闲分量的下标赋值给第k个元素的游标
        return OK;
    }
    return ERROR;
}

Status ListDelete(StaticLinkList L, int i)
{
    int j,k;
    k = MAXSIZE-1;

    if(i<1 || i>ListLength(L)+1) return ERROR;
    for(j=1; j<i; ++j)
        k = L[k].cur;
    L[k].cur = L[i].cur;
    Free_SSL(L, i);
    return OK;
}

/* 打印链表 */
void print(StaticLinkList L)
{
    int j,k;
    k = MAXSIZE-1;

    for(j=1; j<ListLength(L)+1; ++j)
    {
        k = L[k].cur;
        printf("%c ", L[k].data);
    }
}

int main()
{
    StaticLinkList L;
    Status s;

    s = InitList(L);

    s = ListInsert(L, 1, 'a');
    s = ListInsert(L, 1, 'b');
    s = ListInsert(L, 1, 'c');
    s = ListInsert(L, 1, 'd');

    print(L);
    return 0;
}
