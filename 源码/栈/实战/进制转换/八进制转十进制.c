#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define STACT_INIT_SIZE 10
#define STACKINCREMENT 5
#define OK 1
#define ERROR 0

typedef char ElemType;
typedef int Status;

typedef struct
{
    ElemType *base;
    ElemType *top;
    int stacksize;
}SqStack;

Status InitStack(SqStack *S)
{
    S->base = malloc(STACT_INIT_SIZE*sizeof(ElemType));
    if(!(S->base)) exit(0);
    S->top = S->base;
    S->stacksize = STACT_INIT_SIZE;
    return OK;
}

void Push(SqStack *S, ElemType e)
{
    if(S->top - S->base >= S->stacksize)
    {
        S->base = realloc(S->base, (S->stacksize+STACKINCREMENT)*sizeof(ElemType));
        if(!(S->base)) exit(0);
        S->top = S->base+S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *(S->top)++ = e;
}

void Pop(SqStack *S, ElemType *e)
{
    if(S->top == S->base) return;
    *e = *--(S->top);
}

int StackLength(SqStack S)
{
    return (S.top-S.base);
}

int main()
{
    SqStack S;
    ElemType c;
    int i,sum,len;
    sum = 0;

    InitStack(&S);

    printf("请输入八进制数，按#结束\n");
    scanf("%c", &c);
    while(c != '#')
    {
        Push(&S, c);
        scanf("%c", &c);
    }

    //getchar();
    len = StackLength(S);
    printf("当前长度为：%d\n", len);
    for(i=0; i<len; ++i)
    {
        Pop(&S, &c);
        sum = sum + (c-48)*pow(8, i);
    }

    printf("该八进制数的十进制数为：%d\n", sum);
    return 0;
}
