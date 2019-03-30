#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 10
#define STACK_INCREMENT 5
#define MAXBUFFER 50
#define ERROR 0
#define OK 1

static int i=0;             //存放后缀表达式数字的长度，也作为数组下标
static char str[MAXBUFFER]; //存放后缀表达式数组

typedef int Status;

//字符栈,存放后缀表达式
typedef struct Stack_char
{
    char *base;
    char *top;
    int stackSize;
}Stack_char;

//浮点栈，存放后缀表达式求值结果
typedef struct Stack_double
{
    double *base;
    double *top;
    int stackSize;
}Stack_double;

//初始化栈
Status initStack_char(Stack_char *S)
{
    S->base = malloc(STACK_INIT_SIZE * sizeof(Stack_char));
    if(!(S->base)) exit(0);
    S->top = S->base;
    S->stackSize = STACK_INIT_SIZE;
    return OK;
}

Status initStack_double(Stack_double *S)
{
    S->base = malloc(STACK_INIT_SIZE * sizeof(Stack_double));
    if(!(S->base)) exit(0);
    S->top = S->base;
    S->stackSize = STACK_INIT_SIZE;
    return OK;
}

//计算栈长度
int stackLength_char(Stack_char S)
{
    return (S.top - S.base);
}

int stackLength_double(Stack_double S)
{
    return (S.top - S.base);
}

//压栈
Status push_char(Stack_char *S, char e)
{
    if((S->top - S->base) >= S->stackSize)
    {
        S->base = realloc(S->base, (S->stackSize + STACK_INCREMENT) * sizeof(Stack_char));
        if(!(S->base)) exit(0);
        S->top = S->base + S->stackSize;
        S->stackSize += STACK_INCREMENT;
    }
    *(S->top)++ = e;
    return OK;
}

Status push_double(Stack_double *S, double e)
{
    if((S->top - S->base) >= S->stackSize)
    {
        S->base = realloc(S->base, (S->stackSize + STACK_INCREMENT) * sizeof(Stack_double));
        if(!(S->base)) exit(0);
        S->top = S->base + S->stackSize;
        S->stackSize += STACK_INCREMENT;
    }
    *(S->top)++ = e;
    return OK;
}

//弹栈
Status pop_char(Stack_char *S, char *e)
{
    if(S->top == S->base) return ERROR;
    *e = *--(S->top);
    return OK;
}

Status pop_double(Stack_double *S, double *e)
{
    if(S->top == S->base) return ERROR;
    *e = *--(S->top);
    return OK;
}

//获取栈顶元素（不弹出）
Status getTop_char(Stack_char S, char *e)
{
    if(S.top == S.base) return ERROR;
    pop_char(&S, e);     //注意这里的e指的是*e的地址
    push_char(&S, *e);
    return OK;
}

/* 中缀表达式转后缀表达式 */
void transform(Stack_char S)
{
    char c, e;  //c接收客户端字符,e接收栈顶字符
    int j;

    printf("Please input the formula, press # to finish: ");
    scanf("%c", &c);
    while(c != '#')
    {
        //如果字符为数字，直接输出
        if((c >= '0' && c <= '9') || c == '.')      //支持小数
        {
            str[i++] = c;
        }
        /* 如果字符为+或-，若栈为空或者栈顶为'('，将字符压入栈中；
         * 若栈非空或者栈顶非'('，将元素全部弹出并输出，再将字符压入栈中
         */
        else if('+' == c || '-' == c)
        {
            getTop_char(S, &e);
            if(stackLength_char(S) == 0 || '(' == e)
            {
                push_char(&S, c);
                str[i++] = ' ';    //每压入一个操作符则打印一个空格，当c为左括号除外，下同
            }else
            {
                do
                {
                    pop_char(&S, &e);
                    str[i++] = ' ';
                    str[i++] = e;
                }while(stackLength_char(S) != 0);
                push_char(&S, c);
                str[i++] = ' ';
            }
        }
        /* 如果字符为*或/，若栈为空或者栈顶为'('，将字符压入栈中；
         * 若栈非空或者栈顶非'('，判断与栈顶字符优先级，
         * 若等于，则将栈顶字符弹出并输出，再将字符压入栈中；否则直接压入栈中
         */
        else if('*' == c || '/' == c)
        {
            getTop_char(S, &e);
            if(stackLength_char(S) == 0 || '(' == e)
            {
                push_char(&S, c);
                str[i++] = ' ';
            }else
            {
                if('*' == e || '/' == e)
                {
                    pop_char(&S, &e);
                    str[i++] = ' ';
                    str[i++] = e;
                    push_char(&S, c);
                    str[i++] = ' ';
                }else
                {
                    push_char(&S, c);
                    str[i++] = ' ';
                }
            }
        }
        //如果字符为'('，直接将字符压入栈中
        else if('(' == c)
        {
            push_char(&S, c);
        }
        //如果字符为')'，将栈中字符逐个弹出并输出，直到遇到'('为止，并将'('弹出（不输出）
        else if(')' == c)
        {
            do
            {
                pop_char(&S, &e);
                if(e != '(')
                {
                    str[i++] = ' ';
                    str[i++] = e;
                }
            }while(e != '(');
        }

        scanf("%c", &c);
    }
    //最后将栈中字符全部弹出并输出
    while(stackLength_char(S) != 0)
    {
        pop_char(&S, &e);
        str[i++] = ' ';
        str[i++] = e;
    }

    /* 打印后缀表达式
    for(j=0; j<i; ++j)
    {
        printf("%c", str[j]);
    }
    */
}


/* 后缀表达式求值 */
double calculate(Stack_double S, char str[])
{
    int j=0;  //循环计数器
    char str2[MAXBUFFER];
    int k=0;      //str2计数器
    char c;
    double a,b,d;


    c = str[j];
    while(j <= i)
    {
        while((c >= '0' && c <= '9') || c == '.')
        {
            str2[k] = c;
            str2[++k] = '\0';

            c = str[++j];
            if(' ' == c)
            {
                d = atof(str2);
                push_double(&S, d);
                k = 0;  //如果不清零会导致内存溢出，程序崩溃
            }
        }
        switch(c)
        {
            case '+':
                pop_double(&S, &a);
                pop_double(&S, &b);
                push_double(&S, b+a);
                break;
            case '-':
                pop_double(&S, &a);
                pop_double(&S, &b);
                push_double(&S, b-a);
                break;
            case '*':
                pop_double(&S, &a);
                pop_double(&S, &b);
                push_double(&S, b*a);
                break;
            case '/':
                pop_double(&S, &a);
                pop_double(&S, &b);
                if(0 == a) printf("除数不能为零\n");
                else push_double(&S, b/a);
                break;
        }
        c = str[++j];
    }


    pop_double(&S, &d);
    return d;
}




int main()
{
    Stack_char S1;
    Stack_double S2;

    initStack_char(&S1);
    transform(S1);   //调用该函数接收中缀表达式，并将其转换为后缀表达式

    initStack_double(&S2);
    printf("The result is: %.2f", calculate(S2, str));  //后缀表达式求值，并输出最终结果
    return 0;
}

