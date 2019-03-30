/* 规则：
 * 1. 如果输入的字符为数字，则放入数组，并以'\0'结束；继续接收客户端输入的下一个字符，如果为空格，则将数组转换为double型数据，压入栈中，数组计数器清零
 * 2. 如果输入的字符为操作符，从栈中相继弹出两个数据，进行相应的操作运算，并将计算结果压入栈中
 * 3. 最后弹栈，将最终计算结果打印出来
 */

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 10
#define STACK_INCREMENT 5
#define MAXBUFFER 10
#define ERROR 0
#define OK 1

typedef double ElemType;    //这里用double型，存储字符串转换后的double型数据，char明显不适用
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
    char c;
    char str[MAXBUFFER];
    int i=0;
    double a,b,d;

    initStack(&S);

    printf("请输入逆波兰表达式，用空格隔开，按#结束：");
    scanf("%c", &c);
    while(c != '#')
    {
        while((c >= '0' && c <= '9') || c == '.')
        {
            str[i] = c;
            str[++i] = '\0';

            scanf("%c", &c);
            if(' ' == c)
            {
                d = atof(str);
                push(&S, d);
                i = 0;  //如果不清零会导致内存溢出，程序崩溃
            }
        }
        switch(c)
        {
            case '+':
                pop(&S, &a);
                pop(&S, &b);
                push(&S, b+a);
                break;
            case '-':
                pop(&S, &a);
                pop(&S, &b);
                push(&S, b-a);
                break;
            case '*':
                pop(&S, &a);
                pop(&S, &b);
                push(&S, b*a);
                break;
            case '/':
                pop(&S, &a);
                pop(&S, &b);
                if(0 == a) printf("除数不能为零\n");
                else push(&S, b/a);
                break;
        }
        scanf("%c", &c);
    }
    pop(&S, &d);
    printf("最终计算结果为: %f", d);

    return 0;
}
