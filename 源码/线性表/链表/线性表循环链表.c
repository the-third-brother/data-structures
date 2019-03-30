/* 循环链表与单向链表的区别在于，循环条件不再是判断p或p->next是否为空
 * 而是判断p->next是否指向头指针，以下代码会有标明与单向链表的不同之处
 */
#include <stdio.h>
#include <stdlib.h>
#include "time.h"

#define OK 1
#define ERROR 0
#define FALSE 0

typedef int ElemType;
typedef int Status;


typedef struct NODE
{
    ElemType data;
    struct NODE *next;
}NODE;

typedef struct NODE *LinkList;

/* 整表创建（头插法） */
Status CreateListHead(LinkList *L, int n)
{
    int i;
    LinkList p;

    *L = (LinkList)malloc(sizeof(NODE));
    (*L)->next = *L;    //指向头指针，此处与单向链表不同
    srand(time(0));

    for(i=0; i<n; ++i)
    {
        p = (LinkList)malloc(sizeof(NODE));
        p->data = rand()%100;
        p->next = (*L)->next;
        (*L)->next = p;
    }
    return OK;
}

/* 整表创建（尾插法） */
Status CreateListTail(LinkList *L, int n)
{
    LinkList r,p;
    int i;

    *L = (LinkList)malloc(sizeof(NODE));
    r = *L;

    srand(time(0));
    for(i=0; i<n; ++i)
    {
        p = (LinkList)malloc(sizeof(NODE));
        p->data = rand()%100;
        r->next = p;
        r = p;
    }
    r->next = *L;   //指向头指针，此处与单向链表不同
    return OK;
}

/* 插入元素 */
Status ListInsert(LinkList *L, int i, ElemType e)
{
    LinkList p,s;
    int j=1;

    p = *L;
    while((p->next)!=(*L) && j<i)     //此处与单向链表不同
    {
        p = p->next;
        ++j;
    }
    if(!p || j>i) return ERROR;

    s = (LinkList)malloc(sizeof(NODE));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

/* 删除元素 */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
    LinkList p,q;
    int j=1;

    p = *L;
    while((p->next)!=(*L) && j<i)   //此处与单向链表不同
    {
        p = p->next;
        ++j;
    }
    if((p->next)==*L || j>i) return ERROR;  //此处与单向链表不同
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}

/* 算法1：获取元素
Status GetElem(LinkList L, int i, ElemType *e)
{
    LinkList p;
    int j=1;

    p = L;
    while(p && j<i)
    {
        p = p->next;
        ++j;
    }
    if(!p || j>i) return ERROR;
    *e = p->next->data;
    return OK;
}
*/

/* 算法2（推荐）：获取元素 */
Status GetElem(LinkList L, int i, ElemType *e)
{
    LinkList p;
    int j=1;

    p = L->next;    //指向第j个元素
    while(p && j<i)
    {
        p = p->next;
        ++j;
    }
    if(!p || j>i) return ERROR;
    *e = p->data;
    return OK;
}

/* 算法1：定位元素
int LocateElem(LinkList L,ElemType e)
{
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        if(p->data==e) //找到这样的数据元素
                return i;
        p=p->next;
    }

    return 0;
}
*/

/* 算法2（推荐）：定位元素 */
int LocateElem(LinkList L, ElemType e)
{
    LinkList p;
    int j=1;

    p = L->next;    //指向第j个元素
    while(p != L)   //判断是否指向头指针，此处与单向链表不同
    {
        if((p->data) == e)
        {
            return j;
        }
        p = p->next;
        ++j;
    }
    return FALSE;
}

/* 打印链表 */
void print(LinkList L)
{
    LinkList p;
    p = L->next;

    if(p == L) printf("链表为空！");     //判断是否指向头指针，此处与单向链表不同
    while(p != L)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    LinkList p,q;
    int i;
    int s;
    ElemType e;

    s = CreateListHead(&p, 10);
    if(s)
    {
        printf("链表创建成功（头插法）：");
        print(p);
    }
    else printf("链表创建失败\n");

    s = CreateListTail(&q, 0);
    if(s)
    {
        printf("链表创建成功（尾插法）：");
        print(q);
    }
    else printf("链表创建失败\n");

    s = ListInsert(&p, 4, 100);
    if(s)
    {
        printf("插入链表第四个元素成功！");
        print(p);
    }
    else printf("链表插入失败!\n");

    s = ListDelete(&p, 4, &e);
    if(s)
    {
        printf("删除链表第四个元素成功！");
        print(p);
    }
    else printf("删除失败，请判断所删除元素位置是否合法\n");

    s = GetElem(p, 1, &e);
    if(s) printf("查询链表第一个元素成功，该元素为：%d\n", e);
    else printf("查询失败，查询元素位置超过链表长度\n");

    s = LocateElem(p, 100);
    if(s) printf("该元素存在于链表中的第%d个元素\n",s);
    else printf("该元素不存在于链表中\n");
    return 0;
}

