#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

//队列结点结构
typedef struct QNode
{
    ElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

//队列结构
typedef struct
{
    QueuePtr front,rear;    //front指向队首，不存放数据，从front->next开始存放数据；rear指向队尾，即最后一个元素结点
}LinkQueue;

//初始化队列
Status InitQueue(LinkQueue *Q)
{
    Q->front = Q->rear = malloc(sizeof(QNode));     //队尾指向队首，表示队列为空
    if(!(Q->front)) exit(0);
    Q->front->next = NULL;
    return OK;
}

//队尾插入新结点
Status EnQueue(LinkQueue *Q, ElemType e)
{
    QueuePtr s = malloc(sizeof(QNode));
    if(!s) exit(0);
    s->data= e;
    s->next = NULL;
    Q->rear->next = s;      //队尾链接新节点
    Q->rear = s;            //队尾重新指向新节点
    return OK;
}

//删除队首结点，即front->next
Status DeQueue(LinkQueue *Q, ElemType *e)
{
    QueuePtr p;

    if(Q->front == Q->rear) return ERROR;   //队列为空，返回错误
    p = Q->front->next;                     //取到第一个元素结点
    *e = p->data;                           //取出数据
    Q->front->next = p->next;               //队首指向删除后的队列的第一个元素结点地址
    if(p == Q->rear) Q->rear = Q->front;    //若队列只有一个元素，则队尾指向队首，表示队列为空
    free(p);                                //释放结点
    return OK;
}

//打印队列
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
