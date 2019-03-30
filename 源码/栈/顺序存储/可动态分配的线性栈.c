#include <stdio.h>
#include <stdlib.h>

#define STACT_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

/* ����洢�ṹ */
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stacksize;
}SqStack;

/* ��ʼ�� */
Status InitStack(SqStack *S)
{
    S->base = malloc(STACT_INIT_SIZE*sizeof(ElemType));
    if(!(S->base)) exit(0);
    S->top = S->base;
    S->stacksize = STACT_INIT_SIZE;
    return OK;
}

/* ���ȷ��� */
int ListLength(SqStack S)
{
    return (S.top - S.base);
}

/* ѹջ */
Status Push(SqStack *S, ElemType e)
{
    if(S->top - S->base >= S->stacksize)
    {
        S->base = realloc(S->base, (S->stacksize+STACKINCREMENT)*sizeof(ElemType));
        if(!S->base) exit(0);
        S->top = S->base + S->stacksize;    //�����趨ջ��ָ�룬��Ϊ�洢λ�÷����仯
        S->stacksize += STACKINCREMENT;
    }
    *(S->top)++ = e;
    return OK;
}

/* ��ջ */
Status Pop(SqStack *S, ElemType *e)
{
    if(S->top == S->base) return ERROR;
    *e = *--(S->top);
    return OK;
}

/* ��� */
Status ClearList(SqStack *S)
{
    S->top = S->base;
    return OK;
}

int main()
{
    SqStack S;
    ElemType e;

    InitStack(&S);
    Push(&S, 10);
    Push(&S, 20);

    printf("��ǰ����Ϊ��%d\n", ListLength(S));

    Pop(&S, &e);
    printf("ջ��Ԫ��Ϊ��%d\n", e);

    ClearList(&S);
    printf("��պ�ĳ���Ϊ��%d\n", ListLength(S));
    return 0;
}
