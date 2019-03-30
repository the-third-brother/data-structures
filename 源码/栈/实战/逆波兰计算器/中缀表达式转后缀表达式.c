/* ����
 * 1. ����ַ�Ϊ���֣�ֱ�����
 * 2. ����ַ�Ϊ+��-����ջΪ�ջ���ջ��Ϊ'('�����ַ�ѹ��ջ�У���ջ�ǿջ���ջ����'('����Ԫ��ȫ��������������ٽ��ַ�ѹ��ջ��
 * 3. ����ַ�Ϊ*��/����ջΪ�ջ���ջ��Ϊ'('�����ַ�ѹ��ջ�У���ջ�ǿջ���ջ����'('���ж���ջ���ַ����ȼ��������ڣ���ջ���ַ�������������ٽ��ַ�ѹ��ջ�У�����ֱ��ѹ��ջ��
 * 4. ����ַ�Ϊ'('��ֱ�ӽ��ַ�ѹ��ջ��
 * 5. ����ַ�Ϊ')'����ջ���ַ���������������ֱ������'('Ϊֹ������'('�������������
 * 6. ���ջ���ַ�ȫ�����������
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
    ElemType c, e;  //c���տͻ����ַ�,e����ջ���ַ�

    initStack(&S);

    printf("Please input the formula, press # to finish: ");
    scanf("%c", &c);
    while(c != '#')
    {
        //����ַ�Ϊ���֣�ֱ�����
        if((c >= '0' && c <= '9') || c == '.')      //֧��С��
        {
            printf("%c", c);
        }
        /* ����ַ�Ϊ+��-����ջΪ�ջ���ջ��Ϊ'('�����ַ�ѹ��ջ�У�
         * ��ջ�ǿջ���ջ����'('����Ԫ��ȫ��������������ٽ��ַ�ѹ��ջ��
         */
        else if('+' == c || '-' == c)
        {
            getTop(S, &e);
            if(stackLength(S) == 0 || '(' == e)
            {
                push(&S, c);
                printf(" ");    //ÿѹ��һ�����������ӡһ���ո񣬵�cΪ�����ų��⣬��ͬ
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
        /* ����ַ�Ϊ*��/����ջΪ�ջ���ջ��Ϊ'('�����ַ�ѹ��ջ�У�
         * ��ջ�ǿջ���ջ����'('���ж���ջ���ַ����ȼ���
         * �����ڣ���ջ���ַ�������������ٽ��ַ�ѹ��ջ�У�����ֱ��ѹ��ջ��
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
        //����ַ�Ϊ'('��ֱ�ӽ��ַ�ѹ��ջ��
        else if('(' == c)
        {
            push(&S, c);
        }
        //����ַ�Ϊ')'����ջ���ַ���������������ֱ������'('Ϊֹ������'('�������������
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
    //���ջ���ַ�ȫ�����������
    while(stackLength(S) != 0)
    {
        pop(&S, &e);
        printf(" %c", e);
    }

    return 0;
}
