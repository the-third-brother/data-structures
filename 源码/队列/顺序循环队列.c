#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 10

typedef int ElemType;
typedef int Status;

//˳��ѭ���洢�ṹ
typedef struct
{
    ElemType data[MAXSIZE];
    int front ;
    int rear;
}SqQueue;

//��ʼ������
Status InitQueue(SqQueue *Q)
{
    Q->front = Q->rear = 0;
    return OK;
}

//�����βԪ��
Status EnQueue(SqQueue *Q, ElemType e)
{
    if((Q->rear+1)%MAXSIZE == Q->front) return ERROR;   //�������������ش���
    Q->data[Q->rear] = e;                               //��β��ֵ
    Q->rear = (Q->rear+1)%MAXSIZE;                      //��β��ѭ���ṹ�к���һλ
    return OK;
}

//ɾ������Ԫ��
Status DeQueue(SqQueue *Q, ElemType *e)
{
    if(Q->front == Q->rear) return ERROR;               //����Ϊ�գ����ش���
    *e = Q->data[Q->front];                             //ȡ������
    Q->front = (Q->front+1)%MAXSIZE;                    //������ѭ���ṹ��ǰ��һλ
    return OK;
}

//��ӡ
void print(SqQueue Q)
{
    int i;
    //�Ӷ��ױ�������β
    for(i=Q.front; i<Q.rear; ++i)
        printf("%d ", Q.data[i]);
}

int main()
{
    SqQueue Q;
    ElemType e;

    InitQueue(&Q);

    EnQueue(&Q, 1);
    EnQueue(&Q, 2);
    EnQueue(&Q, 3);

    DeQueue(&Q, &e);

    print(Q);

    return 0;
}
