#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 10

typedef int ElemType;
typedef int Status;

//顺序循环存储结构
typedef struct
{
    ElemType data[MAXSIZE];
    int front ;
    int rear;
}SqQueue;

//初始化队列
Status InitQueue(SqQueue *Q)
{
    Q->front = Q->rear = 0;
    return OK;
}

//插入队尾元素
Status EnQueue(SqQueue *Q, ElemType e)
{
    if((Q->rear+1)%MAXSIZE == Q->front) return ERROR;   //队列已满，返回错误
    Q->data[Q->rear] = e;                               //队尾赋值
    Q->rear = (Q->rear+1)%MAXSIZE;                      //队尾在循环结构中后移一位
    return OK;
}

//删除队首元素
Status DeQueue(SqQueue *Q, ElemType *e)
{
    if(Q->front == Q->rear) return ERROR;               //队列为空，返回错误
    *e = Q->data[Q->front];                             //取出队首
    Q->front = (Q->front+1)%MAXSIZE;                    //队首在循环结构中前移一位
    return OK;
}

//打印
void print(SqQueue Q)
{
    int i;
    //从队首遍历到队尾
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
