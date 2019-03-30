#include <stdio.h>
#include <stdlib.h>

#define STACT_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

/* 定义存储结构 */
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stacksize;
}SqStack;

/* 初始化 */
Status InitStack(SqStack *S)
{
    S->base = malloc(STACT_INIT_SIZE*sizeof(ElemType));
    if(!(S->base)) exit(0);
    S->top = S->base;
    S->stacksize = STACT_INIT_SIZE;
    return OK;
}

/* 长度返回 */
int ListLength(SqStack S)
{
    return (S.top - S.base);
}

/* 压栈 */
Status Push(SqStack *S, ElemType e)
{
    if(S->top - S->base >= S->stacksize)
    {
        S->base = realloc(S->base, (S->stacksize+STACKINCREMENT)*sizeof(ElemType));
        if(!S->base) exit(0);
        S->top = S->base + S->stacksize;    //重新设定栈顶指针，因为存储位置发生变化
        S->stacksize += STACKINCREMENT;
    }
    *(S->top)++ = e;
    return OK;
}

/* 弹栈 */
Status Pop(SqStack *S, ElemType *e)
{
    if(S->top == S->base) return ERROR;
    *e = *--(S->top);
    return OK;
}

/* 清空 */
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

    printf("当前长度为：%d\n", ListLength(S));

    Pop(&S, &e);
    printf("栈顶元素为：%d\n", e);

    ClearList(&S);
    printf("清空后的长度为：%d\n", ListLength(S));
    return 0;
}
