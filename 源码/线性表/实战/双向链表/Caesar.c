#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef char ElemType;
typedef int Status;

typedef struct DuLNode
{
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode, *DuLinkList;

Status InitList(DuLinkList *L)
{
    DuLinkList p,q;
    int i;

    *L = (DuLinkList)malloc(sizeof(DuLNode));
    if(!(*L)) exit(0);
    (*L)->prior = (*L)->next = NULL;

    p = (*L);
    for(i=0; i<26; ++i)
    {
        q = (DuLinkList)malloc(sizeof(DuLNode));
        if(!q) exit(0);
        q->data = 'A'+i;
        q->prior = p;
        q->next = NULL;
        p->next = q;
        p = q;
    }
    p->next = (*L);
    (*L)->prior = p;
}

void caesar(DuLinkList *L, int i)
{
    if(i>0)
    {
        do{(*L) = (*L)->next;}while(--i);
    }
    if(i<0)
    {
        do{(*L) = (*L)->prior;}while(++i);
    }
}

int main()
{
    DuLinkList L;
    int i,j;

    InitList(&L);




    printf("请输入Caesar函数需要的整数：");
    scanf("%d", &i);
    printf("\n");
    caesar(&L, i);
    for(j=0; j<26; ++j)
    {
        L = L->next;
        printf("%c", L->data);
    }
    return 0;
}
