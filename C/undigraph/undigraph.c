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

typedef struct queue_stack
{
    int vertex;
    struct queue_stack *next;
}QS;
typedef struct
{
    struct queue_stack *front;
    struct queue_stack *rear;
} QUEUE;
typedef struct queue_stack *STACK;

bool visited[MAX_VERTEX];
int dfn[MAX_VERTEX];//顶点遍历编号
int count;
AdjGraph Adj_G;//邻接表储存
MTGraph MT_G;//邻接矩阵储存

//队列
void MAKENULL_QUEUE(QUEUE *Q);
void ENQUEUE(QUEUE *Q, int k);
int DEQUEUE(QUEUE *Q);
bool Empty_QUEUE(QUEUE Q);
//栈
STACK MAKENULL_STACK( );
void PUSH(STACK S, int k);
void POP(STACK S);
int TOP(STACK S);

//邻接表和矩阵存储结构建立
void CreateGraph_link(AdjGraph *G_link);
void CreateGraph_matrix(MTGraph *G_Matrix);
//邻接表和矩阵结构相互转换
void Adj_to_MT(AdjGraph *G_link, MTGraph *G_Matrix);//表转换为矩阵
void MT_to_Adj(AdjGraph *G_link, MTGraph *G_Matrix);//矩阵转换为表
//深度优先递归算法
void DFSTraverse_link(AdjGraph G_link, void (*recursiveness)(AdjGraph G_link, int i));
void DFSTraverse_matrix(MTGraph G_Matrix, void (*recursiveness_matrix)(MTGraph G_Matrix, int i));
void DFS_link(AdjGraph G_link, int i);
void DFS_matrix(MTGraph G_Matrix, int i);
//深度优先非递归算法
void Non_DFS_link(AdjGraph G_link, int i);
void Non_DFS_matrix(MTGraph G_matrix, int i);
//广度优先搜索算法
void BFSTraverse_link(AdjGraph G_link);
void BFS_link(AdjGraph G_link, int k);
void BFSTraverse_matrix(MTGraph G_matrix);
void BFS_matrix(MTGraph G_matrix, int k);

//显示数据
void Showlink(AdjGraph G_link);
void Showmatrix(MTGraph G_Matrix);

int main()
{
    bool g_l = false, g_m = false; //判断是否建立储存结构
    int cho = 1;
    AdjGraph G_link;
    MTGraph G_matrix;
    while (cho != 0)
    {
        system("cls");
        printf("--------------------------------\n");
        printf("--            0.Quit          --\n");
        printf("--   1.Create Adjacency List  --\n");
        printf("--  2.Create Adjacency Matrix --\n");
        printf("--      3.List to Matrix      --\n");
        printf("--      4.Matrix to List      --\n");
        printf("--   5.DFS List Recursively   --\n");
        printf("--  6.DFS Matrix Recursively  --\n");
        printf("-- 7.DFS List Non_recursively --\n");
        printf("--8.DFS Matrix Non_recursively--\n");
        printf("--         9.BFS List         --\n");
        printf("--       10.BFS Matrix        --\n");
        printf("--------------------------------\n");
        printf("Which do you wanna choose? ");
        scanf("%d", &cho);
        switch (cho)
        {
        case 0://Quit
            printf("Quit successfully!\n");
            break;
        case 1://Create Adjacency List
            CreateGraph_link(&G_link);
            g_l = true;
            printf("\nThe Created Graph:");
            Showlink(G_link);
            system("pause");
            break;
        case 2://Create Adjacency Matrix
            CreateGraph_matrix(&G_matrix);
            g_m = true;
            printf("\nThe Created Graph:");
            Showmatrix(G_matrix);
            system("pause");
            break;
        case 3://List to Matrix
            if (g_l == false)
            {
                printf("Create no adjacency list.\n");
                system("pause");
            }
            else
            {
                Adj_to_MT(&G_link, &G_matrix);
                g_m = true;
                printf("\nThe Earlier Graph:");
                Showlink(G_link);
                printf("\n\nThe Created Graph:");
                Showmatrix(G_matrix);
                system("pause");
            }
            break;
        case 4://Matrix to List
            if (g_m == false)
            {
                printf("Create no adjacency matrix.\n");
                system("pause");
            }
            else
            {
                MT_to_Adj(&G_link, &G_matrix);
                g_l = true;
                printf("\nThe Earlier Graph:");
                Showmatrix(G_matrix);
                printf("\n\nThe Created Graph:");
                Showlink(G_link);
                system("pause");
            }
            break;
        case 5://DFS List Recursively
            if (g_l == false)
            {
                printf("Create no adjacency list.\n");
                system("pause");
            }
            else
            {
                DFSTraverse_link(G_link, DFS_link);
                printf("\n\nThe Spanning forest");
                Showlink(Adj_G);
                system("pause");
            }
            break;
        case 6://DFS Matrix Recursively
            if (g_m == false)
            {
                printf("Create no adjacency matrix.\n");
                system("pause");
            }
            else
            {
                DFSTraverse_matrix(G_matrix, DFS_matrix);
                printf("\n\nThe Spanning forest");
                Showmatrix(MT_G);
                system("pause");
            }
            break;
        case 7://DFS List Non_recursively
            if (g_l == false)
            {
                printf("Create no adjacency list.\n");
                system("pause");
            }
            else
            {
                DFSTraverse_link(G_link, Non_DFS_link);
                printf("\n\nThe Spanning forest");
                Showlink(Adj_G);
                system("pause");
            }
            break;
        case 8://DFS Matrix Non_recursively
            if (g_m == false)
            {
                printf("Create no adjacency matrix.\n");
                system("pause");
            }
            else
            {
                DFSTraverse_matrix(G_matrix, Non_DFS_matrix);
                printf("\n\nThe Spanning forest");
                Showmatrix(MT_G);
                system("pause");
            }
            break;
        case 9://BFS List
            if (g_l == false)
            {
                printf("Create no adjacency list.\n");
                system("pause");
            }
            else
            {
                BFSTraverse_link(G_link);
                printf("\n\nThe Spanning forest");
                Showlink(Adj_G);
                system("pause");
            }
            break;
        case 10://BFS Matrix
            if (g_m == false)
            {
                printf("Create no adjacency matrix.\n");
                system("pause");
            }
            else
            {
                BFSTraverse_matrix(G_matrix);
                printf("\n\nThe Spanning forest");
                Showmatrix(MT_G);
                system("pause");
            }
            break;
        default:
            printf("Wrong Choice! Choose again.\n");
            system("pause");
            break;
        }
    }
    return 0;
}

void MAKENULL_QUEUE(QUEUE *Q)
{
    Q->front = (QS *)malloc(sizeof(QS));
    Q->front->next = NULL;
    Q->rear = Q->front;
}
void ENQUEUE(QUEUE *Q, int k)
{
    QS *q = (QS *)malloc(sizeof(QS));
    q->vertex = k;
    q->next = NULL;
    Q->rear->next = q;
    Q->rear = q;
}
int DEQUEUE(QUEUE *Q)
{
    if (Q->front == Q->rear)
        printf("Empty queue.");
    QS *p = Q->front->next;
    Q->front->next = p->next;
    if (p->next == NULL)
        Q->rear = Q->front;
    return p->vertex;
}
bool Empty_QUEUE(QUEUE Q)
{
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}

STACK MAKENULL_STACK( )
{
    STACK s;
    s = (QS *)malloc(sizeof(QS));
    s->next = NULL;
    return s;
}
void PUSH(STACK S, int k)
{
    STACK stk = (QS *)malloc(sizeof(QS));
    stk->vertex = k;
    stk->next = S->next;
    S->next = stk;
}
void POP(STACK S)
{
    int k;
    STACK stk;
    if (S->next)
    {
        stk = S->next;
        S->next = stk->next;
        k = stk->vertex;
        free(stk);
    }
}
int TOP(STACK S)
{
    if(S->next)
        return S->next->vertex;
    else
        return -1;
}

void CreateGraph_link(AdjGraph *G_link)
{
    freopen("input.txt", "r", stdin);
    int head, tail, weight;
    EdgeNode *p;
    scanf("%d%d", &G_link->n, &G_link->e);
    for(int i=0; i<G_link->n; i++)
    {
        scanf("%d", &G_link->vexlist[i].vertex);
        G_link->vexlist[i].firstedge=NULL;
    }
    for (int i = 0; i < G_link->e; i++)
    {
        scanf("%d%d%d", &head, &tail, &weight);
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        p->cost=weight; p->adjvex=tail;
        p->next=G_link->vexlist[head].firstedge;
        G_link->vexlist[head].firstedge=p;
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        p->cost=weight; p->adjvex=head;
        p->next=G_link->vexlist[tail].firstedge;
        G_link->vexlist[tail].firstedge=p;
    }
    freopen("CON", "r", stdin);
}
void CreateGraph_matrix(MTGraph *G_Matrix)
{
    freopen("input.txt", "r", stdin);
    int head, tail, weight;
    int i, j;
    //printf("How many vertices and edges?");
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
    freopen("CON", "r", stdin);
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

void DFSTraverse_link(AdjGraph G_link, void (*recursiveness_link)(AdjGraph G_link, int i))
{
    int tree = 1;
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
        {
            printf("\nTREE %d: ", tree++);
            (*recursiveness_link)(G_link, i);
        }
}
void DFS_link(AdjGraph G_link, int i)
{
    EdgeNode *p, *q;
    printf("%d ", i);
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
void DFSTraverse_matrix(MTGraph G_Matrix, void (*recursiveness_matrix)(MTGraph G_Matrix, int i))
{
    int tree = 1;
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
        {
            printf("\nTREE %d: ", tree++);
            (*recursiveness_matrix)(G_Matrix, i);
        }
}
void DFS_matrix(MTGraph G_Matrix, int i)
{
    int j;
    printf("%d ", i);
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
    int tree = 1;
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
            printf("\nTREE %d:", tree++);
            BFS_link(G_link, i);
        }
    }
}
void BFS_link(AdjGraph G_link, int k)
{
    int i;
    EdgeNode *p, *q;
    QUEUE Q;
    MAKENULL_QUEUE(&Q);
    printf("%d ", k);
    visited[k] = true;
    dfn[k] = count++;
    ENQUEUE(&Q, k);
    while (!Empty_QUEUE(Q))
    {
        i = DEQUEUE(&Q);
        p = G_link.vexlist[i].firstedge;
        while (p)
        {
            if (!visited[p->adjvex])
            {
                printf("%d ", p->adjvex);
                visited[p->adjvex] = true;
                dfn[p->adjvex] = count++;
                ENQUEUE(&Q, p->adjvex);
                //建立走过的边
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
            }
            p = p->next;
        }
    }
}
void BFSTraverse_matrix(MTGraph G_matrix)
{
    int tree = 1;
    count = 1;
    MT_G.n = G_matrix.n;
    MT_G.e = G_matrix.e;
    for (int i = 0; i < G_matrix.n; i++)
    {
        visited[i] = false;
        MT_G.vertex[i] = G_matrix.vertex[i];
        for (int j = 0; j < G_matrix.n; j++)
            MT_G.edge[i][j] = 0;
    }
    for (int i = 0; i < G_matrix.n; i++)
    {
        if(!visited[i])
        {
            printf("\nTREE %d:", tree++);
            BFS_matrix(G_matrix, i);
        }
    }
}
void BFS_matrix(MTGraph G_matrix, int k)
{
    int i;
    EdgeNode *p;
    QUEUE Q;
    MAKENULL_QUEUE(&Q);
    printf("%d ", k);
    visited[k] = true;
    dfn[k] = count++;
    ENQUEUE(&Q, k);
    while (!Empty_QUEUE(Q))
    {
        i = DEQUEUE(&Q);
        for (int j = 0; j < G_matrix.n; j++)
        {
            if (G_matrix.edge[i][j] > 0 && !visited[j])
            {
                printf("%d ", j);
                visited[j] = true;
                dfn[j] = count++;
                ENQUEUE(&Q, j);
                MT_G.edge[i][j] = G_matrix.edge[i][j];
                MT_G.edge[j][i] = G_matrix.edge[i][j];
            }
        }
    }
}


void Showlink(AdjGraph G_link)
{
    EdgeNode *p;
    printf("\nVertices: Edges\n");
    for (int i = 0; i < G_link.n; i++)
    {
        printf(" %d(%d) :", i, G_link.vexlist[i].vertex);
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
    printf("\nVertices:");
    for (int j = 0; j < G_Matrix.n; j++)
    {
        printf("%d(%d) ", j, G_Matrix.vertex[j]);
    }
    printf("\nAdjacency matrix:\n");
    for (int i = 0; i < G_Matrix.n; i++)
    {
        for (int j = 0; j < G_Matrix.n; j++)
            printf("%d ", G_Matrix.edge[i][j]);
        printf("\n");
    }
}
