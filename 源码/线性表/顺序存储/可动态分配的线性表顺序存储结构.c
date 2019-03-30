#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define INCREMENT 10
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;

typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
}SqList;

/* ���Ա��ʼ�� */
Status InitList(SqList *L)
{
    L->elem = (ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
    if(!L->elem) return ERROR;
    L->length = 0;
    L->listsize = MAXSIZE;
    return OK;
}

/* ���Ա��� */
int ListLength(SqList L)
{
    return L.length;
}
/* ������Ա� */
Status ListEmpty(SqList *L)
{
    L->length = 0;
    return OK;
}

/* ��ȡָ��λ�õ�Ԫ�� */
Status GetElem(SqList L, int i, ElemType *e)
{
    if(i<1 || i>L.length) return ERROR;
    *e = L.elem[i-1];
    return OK;
}

/* ��ѯ���Ա��Ƿ����ָ��Ԫ�� */
int LocateElem(SqList L, ElemType e)
{
    int i;
    for(i=0; i<L.length; ++i)
    {
        if(L.elem[i] == e)
            return ++i;
    }
    return FALSE;
}

/* ���Ա������� */
Status ListInsert(SqList *L, int i, ElemType e)
{
    ElemType *newbase;
    ElemType *p, *q;
    int k;

    if(i<1 || i>L->length+1) return ERROR;
    if(L->length >= MAXSIZE)
    {
        newbase = (ElemType *)realloc(L->elem, sizeof(ElemType)*(L->listsize+INCREMENT));
        if(!newbase) return ERROR;
        L->elem = newbase;
        L->listsize += INCREMENT;
    }
    for(k=L->length-1; k>=i-1; ++k)
        L->elem[k+1] = L->elem[k];
    L->elem[i-1] = e;
    ++L->length;
    return OK;
}

/* ���Ա�ɾ������ */
Status ListDelete(SqList *L, int i, ElemType *e)
{
    int k;
    if(i<1 || i>L->length) return ERROR;
    *e = L->elem[i-1];
    for(k=i; k<L->length; ++k)
    {
        L->elem[k-1] = L->elem[k];
        --L->length;
    }
    return OK;
}

void print(SqList L)
{
    int i;
    for(i=0; i<L.length; ++i)
        printf("%d ", L.elem[i]);
    printf("\n");
}

/* test */
int main()
{
    SqList L;
    Status s;
    ElemType e;
    int i;

    s = InitList(&L);
    if(s) printf("��ʼ���ɹ�����ʼ����ĳ���Ϊ��%d\n", L.length);

    //���Ա��ʼ����ֵ(���������
    for(i=1; i<105; ++i)
        s = ListInsert(&L, i, i);
    if(s)
    {
        printf("\n��ʼ����ֵ������Ա�Ԫ���У�");
        print(L);
        printf("���Ա���Ϊ��%d\n", ListLength(L));
    }else
        printf("���Ա����ʧ��\n");

    //���Ա�ɾ������
    printf("\nɾ�����Ա��һ��Ԫ��\n");
    s = ListDelete(&L, 1, &e);
    if(s)
        printf("����ɾ���ɹ���ɾ����Ԫ��Ϊ��%d\n", e);
    else
        printf("����ɾ��ʧ��\n");

    printf("\n������Ա�\n");
    s = ListEmpty(&L);
    if(s)
        printf("�����ɹ�����ǰ���Ա���Ϊ��%d\n", L.length);
    return 0;
}

