#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 10
#define OK 1
#define ERROR 0

typedef char ElemType;
typedef int Status;

typedef struct
{
    ElemType data[STACK_MAX_SIZE];
    ElemType *top;
    int stackSize;
}Stack;

Status initStack(Stack *S)
{
    *(S->top) = S->data[0];
    S->stackSize = 0;
    return OK;
}

Status push(Stack *S, ElemType e)
{
    *(S->top)++ = e;
    ++S->stackSize;
    return OK;
}

Status pop(Stack *S, ElemType *e)
{
    *e = *--(S->top);
    --S->stackSize;
    return OK;
}

int main()
{
    Stack S;
    ElemType e;

    initStack(&S);
    push(&S, 'a');
    pop(&S, &e);
    printf("%c", e);

    return 0;
}
