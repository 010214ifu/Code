#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_VERTEX 100

typedef struct node
{
    int adjvex;//邻接点
    int cost;//边上的权值
    struct node *next;
}EdgeNode;

typedef struct
{
    int vertex;//顶点数据域
    EdgeNode *firstedge;//边链表表头结点
}VertexNode;

typedef struct
{
    VertexNode vexlist[MAX_VERTEX];
    int n,e;//顶点和边数
}AdjGraph;

typedef struct
{
    int vertex[MAX_VERTEX];//顶点信息
    int edge[MAX_VERTEX][MAX_VERTEX];//边信息
    int n,e;
}MTGraph;

bool visited[MAX_VERTEX];
int dfn[MAX_VERTEX];//顶点遍历编号
int count;
AdjGraph Adj_G;
MTGraph MT_G;

//邻接表和矩阵存储结构建立
void CreateGraph_link(AdjGraph *G_link);
void CreateGraph_matrix(MTGraph *G_Matrix);
//邻接表和矩阵结构相互转换
void Adj_to_MT(AdjGraph *G_link, MTGraph *G_Matrix);//表转换为矩阵
void MT_to_Adj(AdjGraph *G_link, MTGraph *G_Matrix);//矩阵转换为表
//深度优先递归算法
void DFSTraverse_link(AdjGraph G_link);
void DFSTraverse_matrix(MTGraph G_Matrix);
void DFS_link(AdjGraph G_link, int i);
void DFS_matrix(MTGraph G_Matrix, int i);
//深度优先非递归算法

//广度优先搜索算法
void BFSTraverse_link(AdjGraph G_link);
void BFSTraverse_matrix(MTGraph G_matrix);

//显示数据
void Showlink(AdjGraph G_link);
void Showmatrix(MTGraph G_Matrix);

int main()
{
    AdjGraph G_link;
    CreateGraph_link(&G_link);
    Showlink(G_link);
    return 0;
}

void CreateGraph_link(AdjGraph *G_link)
{
    int head, tail, weight;
    EdgeNode *p;
    printf("How many vertices and edges?");
    scanf("%d %d", &G_link->n, &G_link->e);
    for(int i=0; i<G_link->n; i++)
    {
        scanf("%d", &G_link->vexlist[i].vertex);
        G_link->vexlist[i].firstedge=NULL;
    }
    for (int i = 0; i < G_link->e; i++)
    {
        scanf("%d %d %d", &head, &tail, &weight);
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        p->cost=weight; p->adjvex=tail;
        p->next=G_link->vexlist[head].firstedge;
        G_link->vexlist[head].firstedge=p;
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        p->cost=weight; p->adjvex=head;
        p->next=G_link->vexlist[tail].firstedge;
        G_link->vexlist[tail].firstedge=p;
    }
}

void CreateGraph_matrix(MTGraph *G_Matrix)
{
    int head, tail, weight;
    int i, j;
    printf("How many vertices and edges?");
    scanf("%d %d", &G_Matrix->n, &G_Matrix->e);
    for(i=0; i<G_Matrix->n; i++)
    {
        scanf("%d", &G_Matrix->vertex[i]);
        for(j=0; j<G_Matrix->n; j++)//初始化边表
            G_Matrix->edge[i][j]=0;
    }
    for (i = 0; i < G_Matrix->e; i++)
    {
        scanf("%d %d %d", &head, &tail, &weight);
        G_Matrix->edge[head][tail]=weight;
        G_Matrix->edge[tail][head]=weight;
    }
}

void Adj_to_MT(AdjGraph *G_link, MTGraph *G_Matrix)
{
    int i, j;
    EdgeNode *p;
    G_Matrix->n = G_link->n;
    G_Matrix->e = G_link->e;
    for (i = 0; i < G_Matrix->n; i++)//边初始化
        for (j = 0; j < G_Matrix->n; j++)
            G_Matrix->edge[i][j] = 0;
    for (i = 0; i < G_Matrix->n; i++)//顶点赋值
        G_Matrix->vertex[i] = G_link->vexlist[i].vertex;
    for (i = 0; i < G_Matrix->n; i++)//边赋值
    {
        p = G_link->vexlist[i].firstedge;
        while (p != NULL)
        {
            G_Matrix->edge[i][p->adjvex] = p->cost;
            p = p->next;
        }
    }
}

void MT_to_Adj(AdjGraph *G_link, MTGraph *G_Matrix)
{
    int i, j;
    EdgeNode *p;
    G_Matrix->n = G_link->n;
    G_Matrix->e = G_link->e;
    for (i = 0; i < G_link->n; i++)
    {
        G_link->vexlist[i].firstedge = NULL;
        G_link->vexlist[i].vertex = G_Matrix->vertex[i];
    }
    for (i = 0; i < G_link->n; i++)
    {
        for (j = 0; j < G_link->n; j++)
        {
            if (G_Matrix->edge[i][j] != 0)
            {
                p = (EdgeNode *)malloc(sizeof(EdgeNode));
                p->cost = G_Matrix->edge[i][j];
                p->adjvex = j;
                p->next = G_link->vexlist[i].firstedge;
                G_link->vexlist[i].firstedge = p;
            }
        }
    }
}

void DFSTraverse_link(AdjGraph G_link)
{
    count = 1;
    Adj_G.n = G_link.n;
    Adj_G.e = G_link.e;
    for (int i = 0; i < G_link.n; i++)
    {
        visited[i] = false;
        Adj_G.vexlist[i].vertex = G_link.vexlist[i].vertex;
        Adj_G.vexlist[i].firstedge = NULL;
    }
    for (int i = 0; i < G_link.n; i++)
        if (!visited[i])
            DFS_link(G_link, i);
}

void DFS_link(AdjGraph G_link, int i)
{
    EdgeNode *p, *q;
    printf("%d ", G_link.vexlist[i].vertex);
    visited[i] = true;
    dfn[i] = count++;
    p = G_link.vexlist[i].firstedge;
    while (p)
    {
        if (!visited[p->adjvex])
        {
            q = (EdgeNode *)malloc(sizeof(EdgeNode));
            q->cost = p->cost;
            q->adjvex = p->adjvex;
            q->next = Adj_G.vexlist[i].firstedge;
            Adj_G.vexlist[i].firstedge = q;
            q = (EdgeNode *)malloc(sizeof(EdgeNode));
            q->cost = p->cost;
            q->adjvex = i;
            q->next = Adj_G.vexlist[p->adjvex].firstedge;
            Adj_G.vexlist[p->adjvex].firstedge = q;
            DFS_link(G_link, p->adjvex);
        }
        p = p->next;
    }
}

void DFSTraverse_matrix(MTGraph G_Matrix)
{
    count = 1;
    MT_G.n = G_Matrix.n;
    MT_G.e = G_Matrix.e;
    for (int i = 0; i < G_Matrix.n; i++)
    {
        visited[i] = false;
        MT_G.vertex[i] = G_Matrix.vertex[i];
        for (int j = 0; j < MT_G.n; j++)
            MT_G.edge[i][j] = 0;
    }
    for (int i = 0; i < G_Matrix.n; i++)
        if (!visited[i])
            DFS_matrix(G_Matrix, i);
}

void DFS_matrix(MTGraph G_Matrix, int i)
{
    int j;
    printf("%d ", G_Matrix.vertex[i]);
    visited[i] = true;
    dfn[i] = count++;
    for (j = 0; j < G_Matrix.n; j++)
        if ((G_Matrix.edge[i][j] >= 1) && !visited[j])
        {
            MT_G.edge[i][j] = G_Matrix.edge[i][j];
            MT_G.edge[j][i] = G_Matrix.edge[i][j];
            DFS_matrix(G_Matrix, j);
        }
}





void BFSTraverse_link(AdjGraph G_link)
{
    count = 1;
    Adj_G.n = G_link.n;
    Adj_G.e = G_link.e;
    for (int i = 0; i < G_link.n; i++)
    {
        visited[i] = false;
        Adj_G.vexlist[i].vertex = G_link.vexlist[i].vertex;
        Adj_G.vexlist[i].firstedge = NULL;
    }
    for (int i = 0; i < G_link.n; i++)
    {
        if(!visited[i])
        {

        }
    }
}

//void BFSTraverse_matrix(MTGraph G_matrix)







void Showlink(AdjGraph G_link)
{
    EdgeNode *p;
    printf("vertices : edges\n");
    for (int i = 0; i < G_link.n; i++)
    {
        printf("%d :", i);
        p = G_link.vexlist[i].firstedge;
        while (p)
        {
            printf("->%d", p->adjvex);
            p = p->next;
        }
        printf("\n");
    }
}

void Showmatrix(MTGraph G_Matrix)
{
    printf("Vertices:\n");
    for (int i = 0; i < G_Matrix.n; i++)
        printf(" %d", G_Matrix.vertex[i]);
    for (int i = 0; i < G_Matrix.n; i++)
    {
        for (int j = 0; j < G_Matrix.n; j++)
            printf("%d ", G_Matrix.edge[i][j]);
        printf("\n");
    }
}
