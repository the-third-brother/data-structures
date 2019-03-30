#include <stdio.h>

#define MAXSIZE 100
#define INCREMENT 10
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

/* 定义线性表顺序存储结构 */
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
}SqList;

/* 初始化操作 */
Status InitList(SqList *L)
{
    //L->data = (SqList *)malloc(sizeof(ElemType)*MAXSIZE);
    L->length = 0;
    return OK;
}

/* 长度查询 */
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
    *e = L.data[i-1];
    return OK;
}

/* 查询线性表是否存在指定元素 */
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

/* 插入操作（静态插入，无法实现线性表容量增量增长） */
Status ListInsert(SqList *L, int i, ElemType e)
{
    int k;  //循环计数器
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
    int k;  //循环计数器
    if(i<1 || i>L->length) return  ERROR;
    *e = L->data[i-1];   //判断i是否合法
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
    if(s) printf("初始化成功，初始化后的长度为：%d\n", L.length);

    //线性表初始化赋值(插入操作）
    for(i=1; i<5; ++i)
        s = ListInsert(&L, i, i);
    if(s)
    {
        printf("\n初始化赋值后的线性表元素有：");
        print(L);
        printf("线性表长度为：%d\n", ListLength(L));
    }else
        printf("线性表插入失败\n");

    printf("\n获取第一个元素值\n");
    s = GetElem(L, 1, &e);
    if(s) printf("获取成功，该元素值为：%d\n", e);
    else printf("元素获取失败\n");
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
