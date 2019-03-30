#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 10
#define STACK_INCREMENT 5
#define MAXBUFFER 50
#define ERROR 0
#define OK 1

static int i=0;             //��ź�׺���ʽ���ֵĳ��ȣ�Ҳ��Ϊ�����±�
static char str[MAXBUFFER]; //��ź�׺���ʽ����

typedef int Status;

//�ַ�ջ,��ź�׺���ʽ
typedef struct Stack_char
{
    char *base;
    char *top;
    int stackSize;
}Stack_char;

//����ջ����ź�׺���ʽ��ֵ���
typedef struct Stack_double
{
    double *base;
    double *top;
    int stackSize;
}Stack_double;

//��ʼ��ջ
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

//����ջ����
int stackLength_char(Stack_char S)
{
    return (S.top - S.base);
}

int stackLength_double(Stack_double S)
{
    return (S.top - S.base);
}

//ѹջ
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

//��ջ
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

//��ȡջ��Ԫ�أ���������
Status getTop_char(Stack_char S, char *e)
{
    if(S.top == S.base) return ERROR;
    pop_char(&S, e);     //ע�������eָ����*e�ĵ�ַ
    push_char(&S, *e);
    return OK;
}

/* ��׺���ʽת��׺���ʽ */
void transform(Stack_char S)
{
    char c, e;  //c���տͻ����ַ�,e����ջ���ַ�
    int j;

    printf("Please input the formula, press # to finish: ");
    scanf("%c", &c);
    while(c != '#')
    {
        //����ַ�Ϊ���֣�ֱ�����
        if((c >= '0' && c <= '9') || c == '.')      //֧��С��
        {
            str[i++] = c;
        }
        /* ����ַ�Ϊ+��-����ջΪ�ջ���ջ��Ϊ'('�����ַ�ѹ��ջ�У�
         * ��ջ�ǿջ���ջ����'('����Ԫ��ȫ��������������ٽ��ַ�ѹ��ջ��
         */
        else if('+' == c || '-' == c)
        {
            getTop_char(S, &e);
            if(stackLength_char(S) == 0 || '(' == e)
            {
                push_char(&S, c);
                str[i++] = ' ';    //ÿѹ��һ�����������ӡһ���ո񣬵�cΪ�����ų��⣬��ͬ
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
        /* ����ַ�Ϊ*��/����ջΪ�ջ���ջ��Ϊ'('�����ַ�ѹ��ջ�У�
         * ��ջ�ǿջ���ջ����'('���ж���ջ���ַ����ȼ���
         * �����ڣ���ջ���ַ�������������ٽ��ַ�ѹ��ջ�У�����ֱ��ѹ��ջ��
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
        //����ַ�Ϊ'('��ֱ�ӽ��ַ�ѹ��ջ��
        else if('(' == c)
        {
            push_char(&S, c);
        }
        //����ַ�Ϊ')'����ջ���ַ���������������ֱ������'('Ϊֹ������'('�������������
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
    //���ջ���ַ�ȫ�����������
    while(stackLength_char(S) != 0)
    {
        pop_char(&S, &e);
        str[i++] = ' ';
        str[i++] = e;
    }

    /* ��ӡ��׺���ʽ
    for(j=0; j<i; ++j)
    {
        printf("%c", str[j]);
    }
    */
}


/* ��׺���ʽ��ֵ */
double calculate(Stack_double S, char str[])
{
    int j=0;  //ѭ��������
    char str2[MAXBUFFER];
    int k=0;      //str2������
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
                k = 0;  //���������ᵼ���ڴ�������������
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
                if(0 == a) printf("��������Ϊ��\n");
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
    transform(S1);   //���øú���������׺���ʽ��������ת��Ϊ��׺���ʽ

    initStack_double(&S2);
    printf("The result is: %.2f", calculate(S2, str));  //��׺���ʽ��ֵ����������ս��
    return 0;
}

