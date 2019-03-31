#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

//���н��ṹ
typedef struct QNode
{
    ElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

//���нṹ
typedef struct
{
    QueuePtr front,rear;    //frontָ����ף���������ݣ���front->next��ʼ������ݣ�rearָ���β�������һ��Ԫ�ؽ��
}LinkQueue;

//��ʼ������
Status InitQueue(LinkQueue *Q)
{
    Q->front = Q->rear = malloc(sizeof(QNode));     //��βָ����ף���ʾ����Ϊ��
    if(!(Q->front)) exit(0);
    Q->front->next = NULL;
    return OK;
}

//��β�����½��
Status EnQueue(LinkQueue *Q, ElemType e)
{
    QueuePtr s = malloc(sizeof(QNode));
    if(!s) exit(0);
    s->data= e;
    s->next = NULL;
    Q->rear->next = s;      //��β�����½ڵ�
    Q->rear = s;            //��β����ָ���½ڵ�
    return OK;
}

//ɾ�����׽�㣬��front->next
Status DeQueue(LinkQueue *Q, ElemType *e)
{
    QueuePtr p;

    if(Q->front == Q->rear) return ERROR;   //����Ϊ�գ����ش���
    p = Q->front->next;                     //ȡ����һ��Ԫ�ؽ��
    *e = p->data;                           //ȡ������
    Q->front->next = p->next;               //����ָ��ɾ����Ķ��еĵ�һ��Ԫ�ؽ���ַ
    if(p == Q->rear) Q->rear = Q->front;    //������ֻ��һ��Ԫ�أ����βָ����ף���ʾ����Ϊ��
    free(p);                                //�ͷŽ��
    return OK;
}

//��ӡ����
void print(LinkQueue Q)
{
    QueuePtr p;

    p = Q.front->next;
    while(p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}

int main()
{
    LinkQueue Q;
    ElemType e;

    InitQueue(&Q);

    EnQueue(&Q, 1);
    EnQueue(&Q, 2);
    EnQueue(&Q, 3);

    DeQueue(&Q, &e);

    print(Q);

    return 0;
}
