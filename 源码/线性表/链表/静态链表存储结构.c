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

/* ��ʼ�����������α�ȫ����ֵ */
Status InitList(StaticLinkList space)
{
    int i;

    for(i=0; i<MAXSIZE-1; ++i)
        space[i].cur = i+1;
    space[MAXSIZE-1].cur = 0;

    return OK;
}

/* ������нڵ㣬���ؿ��нڵ��±� */
int Malloc_SSL(StaticLinkList space)
{
    int i = space[0].cur;

    if(i)
        space[0].cur = space[i].cur;
    return i;
}

/* ���սڵ� */
void Free_SSL(StaticLinkList space, int k)
{
    space[k].cur = space[0].cur;    //����������ĵ�һ�������α긳ֵ����k��Ԫ�ص��α�
    space[0].cur = k;               //����k��Ԫ�ص��±긳ֵ�����������һ���������α�
}

/* ��ȡ������ */
int ListLength(StaticLinkList L)
{
    int j,k;    //j��ʾ��������k��ʾ��k��Ԫ��
    j = 0;

    k = L[MAXSIZE-1].cur;   //kָ���һ��Ԫ��
    while(k)
    {
        k = L[k].cur;   //kָ����һԪ��
        ++j;            //Ԫ�ظ���+1
    }
    return j;
}

/* ����Ĳ��� */
Status ListInsert(StaticLinkList L, int i, ElemType e)
{
    int j,k,l;      //j��ʾ��������k��ʾ��k��Ԫ��,l��ʾ���з����±�
    k = MAXSIZE-1;  //k��ָ������������

    if(i<1 || i>ListLength(L)+1)    return ERROR;
    l = Malloc_SSL(L);
    if(l)
    {
        L[l].data = e;
        for(j=1; j<i; ++j)
            k = L[k].cur;      //kָ���j��Ԫ��
        L[l].cur = L[k].cur;   //����k��Ԫ�صĵ��α긳ֵ�����з������α�
        L[k].cur = l;           //�����з������±긳ֵ����k��Ԫ�ص��α�
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

/* ��ӡ���� */
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
