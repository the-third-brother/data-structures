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

/* ��������ͷ�巨�� */
Status CreateListHead(LinkList *L, int n)
{
    int i;
    LinkList p;

    *L = (LinkList)malloc(sizeof(NODE));    //����ͷ���
    (*L)->next = NULL;
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

/* ��������β�巨�� */
Status CreateListTail(LinkList *L, int n)
{
    LinkList r,p;
    int i;

    *L = (LinkList)malloc(sizeof(NODE));    //����ͷ���
    r = *L;

    srand(time(0));
    for(i=0; i<n; ++i)
    {
        p = (LinkList)malloc(sizeof(NODE));
        p->data = rand()%100;
        r->next = p;
        r = p;
    }
    r->next = NULL;
    return OK;
}

/* ����Ԫ�� */
Status ListInsert(LinkList *L, int i, ElemType e)
{
    LinkList p,s;
    int j=1;

    p = *L;
    while(p && j<i)
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

/* ɾ��Ԫ�� */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
    LinkList p,q;
    int j=1;

    p = *L;
    while((p->next) && j<i)
    {
        p = p->next;
        ++j;
    }
    if(!(p->next) || j>i) return ERROR;
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}

/* �㷨1����ȡԪ��
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

/* �㷨2���Ƽ�������ȡԪ�� */
Status GetElem(LinkList L, int i, ElemType *e)
{
    LinkList p;
    int j=1;

    p = L->next;    //ָ���j��Ԫ��
    while(p && j<i)
    {
        p = p->next;
        ++j;
    }
    if(!p || j>i) return ERROR;
    *e = p->data;
    return OK;
}

/* �㷨1����λԪ��
int LocateElem(LinkList L,ElemType e)
{
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        if(p->data==e) //�ҵ�����������Ԫ��
                return i;
        p=p->next;
    }

    return 0;
}
*/

/* �㷨2���Ƽ�������λԪ�� */
int LocateElem(LinkList L, ElemType e)
{
    LinkList p;
    int j=1;

    p = L->next;    //ָ���j��Ԫ��
    while(p)
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

/* ��ӡ���� */
void print(LinkList L)
{
    LinkList p;
    p = L->next;

    if(!p) printf("����Ϊ�գ�");
    while(p)
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
        printf("�������ɹ���ͷ�巨����");
        print(p);
    }
    else printf("������ʧ��\n");

    s = CreateListTail(&q, 0);
    if(s)
    {
        printf("�������ɹ���β�巨����");
        print(q);
    }
    else printf("������ʧ��\n");

    s = ListInsert(&p, 1, 100);
    if(s)
    {
        printf("���������һ��Ԫ�سɹ���");
        print(p);
    }
    else printf("�������ʧ��!\n");

    s = ListDelete(&p, 1, &e);
    if(s)
    {
        printf("ɾ�������һ��Ԫ�سɹ���");
        print(p);
    }
    else printf("ɾ��ʧ�ܣ����ж���ɾ��Ԫ��λ���Ƿ�Ϸ�\n");

    s = GetElem(p, 1, &e);
    if(s) printf("��ѯ�����һ��Ԫ�سɹ�����Ԫ��Ϊ��%d\n", e);
    else printf("��ѯʧ�ܣ���ѯԪ��λ�ó���������\n");

    s = LocateElem(p, 100);
    if(s) printf("��Ԫ�ش����������еĵ�%d��Ԫ��\n",s);
    else printf("��Ԫ�ز�������������\n");
    return 0;
}

