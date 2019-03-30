#include <stdio.h>

#define MAXSIZE 100
#define INCREMENT 10
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

/* �������Ա�˳��洢�ṹ */
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
}SqList;

/* ��ʼ������ */
Status InitList(SqList *L)
{
    //L->data = (SqList *)malloc(sizeof(ElemType)*MAXSIZE);
    L->length = 0;
    return OK;
}

/* ���Ȳ�ѯ */
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
    *e = L.data[i-1];
    return OK;
}

/* ��ѯ���Ա��Ƿ����ָ��Ԫ�� */
int LocateElem(SqList L, ElemType e)
{
    int i;
    if(i<1 || i>L.length) return ERROR;
    for(i=0; i<L.length; ++i)
    {
        if(L.data[i] == e)
            return ++i;
    }
    return 0;
}

/* �����������̬���룬�޷�ʵ�����Ա��������������� */
Status ListInsert(SqList *L, int i, ElemType e)
{
    int k;  //ѭ��������
    if(i<1 || i>L->length+1) return ERROR;
    if(L->length == MAXSIZE) return ERROR;
    for(k=L->length-1; k>=i-1; --k)
        L->data[k+1] = L->data[k];
    L->data[i-1] = e;
    ++L->length;
    return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e)
{
    int k;  //ѭ��������
    if(i<1 || i>L->length) return  ERROR;
    *e = L->data[i-1];   //�ж�i�Ƿ�Ϸ�
    for(k=i-1; k<L->length-1; ++k)
        L->data[k] = L->data[k+1];
    --L->length;
    return OK;
}

void print(SqList L)
{
    int i;
    for(i=0; i<L.length; ++i)
        printf("%d ", L.data[i]);
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
    for(i=1; i<5; ++i)
        s = ListInsert(&L, i, i);
    if(s)
    {
        printf("\n��ʼ����ֵ������Ա�Ԫ���У�");
        print(L);
        printf("���Ա���Ϊ��%d\n", ListLength(L));
    }else
        printf("���Ա����ʧ��\n");

    printf("\n��ȡ��һ��Ԫ��ֵ\n");
    s = GetElem(L, 1, &e);
    if(s) printf("��ȡ�ɹ�����Ԫ��ֵΪ��%d\n", e);
    else printf("Ԫ�ػ�ȡʧ��\n");
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
