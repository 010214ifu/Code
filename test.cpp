#include<stdio.h>
#include<stdlib.h>
#define MAX 100


typedef struct node
{
    int adjvex;//邻接点
    int cost;//边上的权值
    struct node *next;
}EdgeNode;

typedef struct
{
    int vertex;//顶点数据域
    EdgeNode *firstedge;//边链表头结点
}VertexNode;

typedef struct
{
    VertexNode vexlist[MAX];
    int n,e;//顶点和边的个数
}AdjGraph;

//邻接表储存结构建立
void CreateGragh(AdjGraph *G);
//广度优先算法
//深度优先算法

int main()
{
    printf("hello world");
    return 0;
}

void CreateGraph(AdjGraph *G)
{
    int head,tail,weight;
    EdgeNode *p;
    scanf("%d %d",G->n,G->e);
    for(int i=0; i<G->n; i++)
    {
        scanf("%d",&G->vexlist[i].vertex);
        G->vexlist[i].firstedge=NULL;
    }
    for(int j=0; j<G->e; j++)
    {
        scanf("%d %d %d",&head, &tail, &weight);
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        p->adjvex=head; p->cost=weight;
        p->next=G->vexlist[tail].firstedge;
        G->vexlist[tail].firstedge=p;
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        p->adjvex=tail; p->cost=weight;
        p->next=G->vexlist[head].firstedge;
        G->vexlist[head].firstedge=p;
    }
}
