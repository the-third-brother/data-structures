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

/* 线性表初始化 */
Status InitList(SqList *L)
{
    L->elem = (ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
    if(!L->elem) return ERROR;
    L->length = 0;
    L->listsize = MAXSIZE;
    return OK;
}

/* 线性表长度 */
int ListLength(SqList L)
{
    return L.length;
}
/* 清空线性表 */
Status ListEmpty(SqList *L)
{
    L->length = 0;
    return OK;
}

/* 获取指定位置的元素 */
Status GetElem(SqList L, int i, ElemType *e)
{
    if(i<1 || i>L.length) return ERROR;
    *e = L.elem[i-1];
    return OK;
}

/* 查询线性表是否存在指定元素 */
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

/* 线性表插入操作 */
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

/* 线性表删除操作 */
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
    if(s) printf("初始化成功，初始化后的长度为：%d\n", L.length);

    //线性表初始化赋值(插入操作）
    for(i=1; i<105; ++i)
        s = ListInsert(&L, i, i);
    if(s)
    {
        printf("\n初始化赋值后的线性表元素有：");
        print(L);
        printf("线性表长度为：%d\n", ListLength(L));
    }else
        printf("线性表插入失败\n");

    //线性表删除操作
    printf("\n删除线性表第一个元素\n");
    s = ListDelete(&L, 1, &e);
    if(s)
        printf("数据删除成功，删除的元素为：%d\n", e);
    else
        printf("数据删除失败\n");

    printf("\n清空线性表\n");
    s = ListEmpty(&L);
    if(s)
        printf("操作成功，当前线性表长度为：%d\n", L.length);
    return 0;
}

