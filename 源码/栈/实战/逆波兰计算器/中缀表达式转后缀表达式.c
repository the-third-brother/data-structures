/* 规则：
 * 1. 如果字符为数字，直接输出
 * 2. 如果字符为+或-，若栈为空或者栈顶为'('，将字符压入栈中；若栈非空或者栈顶非'('，将元素全部弹出并输出，再将字符压入栈中
 * 3. 如果字符为*或/，若栈为空或者栈顶为'('，将字符压入栈中；若栈非空或者栈顶非'('，判断与栈顶字符优先级，若等于，则将栈顶字符弹出并输出，再将字符压入栈中；否则直接压入栈中
 * 4. 如果字符为'('，直接将字符压入栈中
 * 5. 如果字符为')'，将栈中字符逐个弹出并输出，直到遇到'('为止，并将'('弹出（不输出）
 * 6. 最后将栈中字符全部弹出并输出
 */

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 10
#define STACK_INCREMENT 5
#define ERROR 0
#define OK 1

typedef char ElemType;
typedef int Status;

typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}Stack;

//初始化栈
Status initStack(Stack *S)
{
    S->base = malloc(STACK_INIT_SIZE * sizeof(Stack));
    if(!(S->base)) exit(0);
    S->top = S->base;
    S->stackSize = STACK_INIT_SIZE;
    return OK;
}

//计算栈长度
int stackLength(Stack S)
{
    return (S.top - S.base);
}

//压栈
Status push(Stack *S, ElemType e)
{
    if((S->top - S->base) >= S->stackSize)
    {
        S->base = realloc(S->base, (S->stackSize + STACK_INCREMENT) * sizeof(Stack));
        if(!(S->base)) exit(0);
        S->top = S->base + S->stackSize;
        S->stackSize += STACK_INCREMENT;
    }
    *(S->top)++ = e;
    return OK;
}

//弹栈
Status pop(Stack *S, ElemType *e)
{
    if(S->top == S->base) return ERROR;
    *e = *--(S->top);
    return OK;
}

//获取栈顶元素（不弹出）
Status getTop(Stack S, ElemType *e)
{
    if(S.top == S.base) return ERROR;
    pop(&S, e);     //注意这里的e指的是*e的地址
    push(&S, *e);
    return OK;
}

int main()
{
    Stack S;
    ElemType c, e;  //c接收客户端字符,e接收栈顶字符

    initStack(&S);

    printf("Please input the formula, press # to finish: ");
    scanf("%c", &c);
    while(c != '#')
    {
        //如果字符为数字，直接输出
        if((c >= '0' && c <= '9') || c == '.')      //支持小数
        {
            printf("%c", c);
        }
        /* 如果字符为+或-，若栈为空或者栈顶为'('，将字符压入栈中；
         * 若栈非空或者栈顶非'('，将元素全部弹出并输出，再将字符压入栈中
         */
        else if('+' == c || '-' == c)
        {
            getTop(S, &e);
            if(stackLength(S) == 0 || '(' == e)
            {
                push(&S, c);
                printf(" ");    //每压入一个操作符则打印一个空格，当c为左括号除外，下同
            }else
            {
                do
                {
                    pop(&S, &e);
                    printf(" %c", e);
                }while(stackLength(S) != 0);
                push(&S, c);
                printf(" ");
            }
        }
        /* 如果字符为*或/，若栈为空或者栈顶为'('，将字符压入栈中；
         * 若栈非空或者栈顶非'('，判断与栈顶字符优先级，
         * 若等于，则将栈顶字符弹出并输出，再将字符压入栈中；否则直接压入栈中
         */
        else if('*' == c || '/' == c)
        {
            getTop(S, &e);
            if(stackLength(S) == 0 || '(' == e)
            {
                push(&S, c);
                printf(" ");
            }else
            {
                if('*' == e || '/' == e)
                {
                    pop(&S, &e);
                    printf(" %c", e);
                    push(&S, c);
                    printf(" ");
                }else
                {
                    push(&S, c);
                    printf(" ");
                }
            }
        }
        //如果字符为'('，直接将字符压入栈中
        else if('(' == c)
        {
            push(&S, c);
        }
        //如果字符为')'，将栈中字符逐个弹出并输出，直到遇到'('为止，并将'('弹出（不输出）
        else if(')' == c)
        {
            do
            {
                pop(&S, &e);
                if(e != '(') printf(" %c", e);
            }while(e != '(');
        }

        scanf("%c", &c);
    }
    //最后将栈中字符全部弹出并输出
    while(stackLength(S) != 0)
    {
        pop(&S, &e);
        printf(" %c", e);
    }

    return 0;
}
