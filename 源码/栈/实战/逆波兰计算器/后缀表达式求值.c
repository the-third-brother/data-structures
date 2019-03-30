/* ����
 * 1. ���������ַ�Ϊ���֣���������飬����'\0'�������������տͻ����������һ���ַ������Ϊ�ո�������ת��Ϊdouble�����ݣ�ѹ��ջ�У��������������
 * 2. ���������ַ�Ϊ����������ջ����̵����������ݣ�������Ӧ�Ĳ������㣬����������ѹ��ջ��
 * 3. ���ջ�������ռ�������ӡ����
 */

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 10
#define STACK_INCREMENT 5
#define MAXBUFFER 10
#define ERROR 0
#define OK 1

typedef double ElemType;    //������double�ͣ��洢�ַ���ת�����double�����ݣ�char���Բ�����
typedef int Status;

typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}Stack;

//��ʼ��ջ
Status initStack(Stack *S)
{
    S->base = malloc(STACK_INIT_SIZE * sizeof(Stack));
    if(!(S->base)) exit(0);
    S->top = S->base;
    S->stackSize = STACK_INIT_SIZE;
    return OK;
}

//����ջ����
int stackLength(Stack S)
{
    return (S.top - S.base);
}

//ѹջ
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

//��ջ
Status pop(Stack *S, ElemType *e)
{
    if(S->top == S->base) return ERROR;
    *e = *--(S->top);
    return OK;
}

//��ȡջ��Ԫ�أ���������
Status getTop(Stack S, ElemType *e)
{
    if(S.top == S.base) return ERROR;
    pop(&S, e);     //ע�������eָ����*e�ĵ�ַ
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

    printf("�������沨�����ʽ���ÿո��������#������");
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
                i = 0;  //���������ᵼ���ڴ�������������
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
                if(0 == a) printf("��������Ϊ��\n");
                else push(&S, b/a);
                break;
        }
        scanf("%c", &c);
    }
    pop(&S, &d);
    printf("���ռ�����Ϊ: %f", d);

    return 0;
}
