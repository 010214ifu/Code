#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
//INT_MAX  INT_MIN
#include<stdbool.h>
#define MAX_VERTEX 100


typedef struct
{
    int sub;
    int path_length;
}HeapNode;

typedef struct
{
    HeapNode data[MAX_VERTEX+1];
    int n;
}HEAP;

typedef struct
{
    char vertex[MAX_VERTEX];//顶点信息
    int edge[MAX_VERTEX+1][MAX_VERTEX+1];//边信息
    int n,e;
}MTGraph;

typedef struct stack
{
    int vertex;
    struct stack *next;
}*STACK;


MTGraph G;
HEAP Min_Heap;


int D_SPF[MAX_VERTEX + 1];
int P_SPF[MAX_VERTEX + 1];
bool S_SPF[MAX_VERTEX + 1];

int D_Floyd[MAX_VERTEX+1][MAX_VERTEX+1];
int P_Floyd[MAX_VERTEX+1][MAX_VERTEX+1];
bool reachable_matrix[MAX_VERTEX+1][MAX_VERTEX+1];
int path_Floyd[MAX_VERTEX+1][MAX_VERTEX+1];

//创建空堆
void MakeNullHeap();
//判断空堆
bool HeapEmpty();
//判断满堆
bool HeapFull();
//初始化堆
void HeapInit();
//堆插入
void Insert(int sub, int path_length);
//堆删除任意位置元素，返回角标
int DeleteData(int k);

//栈
STACK MAKENULL_STACK( );
void PUSH(STACK S, int k);
int POP(STACK S);
//int TOP(STACK S);



//邻接矩阵存储结构有向图建立
void CreateGraph_matrix();
//Dijkstra算法
void Dijkstra(int source);
void Dijkstra_path(int source, int target);
//Floyd算法
void Floyd();
void Floyd_path(int source, int target);
//有向图可达矩阵
void Floyd_reachable_matrix();
//展示图
void Showmatrix(MTGraph G);



int main()
{
    CreateGraph_matrix();
    printf("BGIU");
    Dijkstra(2);
    printf("GUIGB");
    Dijkstra_path(2, 4);
    return 0;
}



STACK MAKENULL_STACK( )
{
    STACK s;
    s = (struct stack *)malloc(sizeof(struct stack));
    s->next = NULL;
    return s;
}
void PUSH(STACK S, int k)
{
    STACK stk = (struct stack *)malloc(sizeof(struct stack));
    stk->vertex = k;
    stk->next = S->next;
    S->next = stk;
}
int POP(STACK S)
{
    int k;
    STACK stk;
    if (S->next)
    {
        stk = S->next;
        S->next = stk->next;
        k = stk->vertex;
        free(stk);
        return k;
    }
    else
        return -1;
}

void MakeNullHeap()
{
    Min_Heap.n = 0;
}
bool HeapEmpty()
{
    return (!Min_Heap.n);
}
bool HeapFull()
{
    return (Min_Heap.n==MAX_VERTEX);
}
void HeapInit()
{
    for (int i = 1; i <= G.n; i++)
        Insert(i, D_SPF[i]);
}

void Insert(int sub, int path_length)
{
    int i = 1;
    if(!HeapFull())
    {
        i = Min_Heap.n + 1;
        while ((i != 1) && (path_length < Min_Heap.data[i / 2].path_length))
        {
            Min_Heap.data[i] = Min_Heap.data[i / 2];
            i /= 2;
        }
        
    }
    Min_Heap.data[i].sub = sub;
    Min_Heap.data[i].path_length = path_length;
    Min_Heap.n++;
}
int DeleteData(int k)
{
    int parent = k, child = 2 * k;
    HeapNode elem, tmp;
    if (!HeapEmpty())
    {
        elem = Min_Heap.data[parent];
        tmp = Min_Heap.data[Min_Heap.n--];
        while (child <= Min_Heap.n)
        {
            if ((child < Min_Heap.n) && (Min_Heap.data[child].path_length > Min_Heap.data[child + 1].path_length))
                child++;
            if (tmp.path_length <= Min_Heap.data[child].path_length)
                break;
            Min_Heap.data[parent] = Min_Heap.data[child];
            parent = child;
            child *= 2;
        }
        Min_Heap.data[parent] = tmp;
        return elem.sub;
    }
}


void CreateGraph_matrix( )
{
    freopen("input.txt", "r", stdin);
    int head, tail, weight;
    int i, j;
    scanf("%d %d", &G.n, &G.e);
    for (i = 1; i <= G.n; i++)
    {
        scanf("%c", &G.vertex[i]);
        for (j = 1; j <= G.n; j++) //初始化边表
        {
            G.edge[i][j] = INT_MAX;
        }
    }
    for (i = 1; i <= G.e; i++)
    {
        scanf("%d %d %d", &head, &tail, &weight);
        G.edge[head][tail]=weight;
    }
    freopen("CON", "r", stdin);
}

void Dijkstra(int source)
{
    int i, v, w, sum, t;
    for (i = 1; i <= G.n; i++)
    {
        D_SPF[i] = G.edge[source][i];
        S_SPF[i] = false;
    }
    S_SPF[source] = true;
    MakeNullHeap();
    HeapInit();
    for (i = 1; i < G.n; i++)
    {
        //w = MinCost();//求最小值的同时删除，后面补位
        w = DeleteData(1);
        S_SPF[w] = true;
        ;
        for ( v = 0; v < Min_Heap.n; v++)
        {
            sum = D_SPF[w] + G.edge[w][Min_Heap.data[v].sub];
            if (sum < D_SPF[v])
            {
                D_SPF[Min_Heap.data[v].sub] = sum;
                t = DeleteData(v);
                Insert(t, sum);
                //D[v] = sum;
                //delete,,,insert
                P_SPF[v] = w;
            }
        }
        /*
        for ( v = 0; v <= G.n; v++)
        {
            if (S[v] != true)
            {
                sum = D[w] + G.edge[w][v];
                if (sum < D[v])
                {
                    D[v] = sum;
                    P[v] = w;
                }
            }
        }
        */
    }
}

void Dijkstra_path(int source, int target)
{
    STACK s = MAKENULL_STACK();
    PUSH(s, target);
    //target入栈
    int pre = P_SPF[target];
    while (pre != source)
    {
        //pre入栈
        PUSH(s, pre);
        pre = P_SPF[pre];
    }
    printf("Path: %c", G.vertex[pre]);
    while (s->next != NULL)
    {
        printf("-->%c", G.vertex[POP(s)]);
    }
    
}

void Floyd()
{
    int i, j, k;
    for ( i = 1; i <= G.n; i++)
        for (j = 1; j <= G.n; j++)
        {
            D_Floyd[i][j] = G.edge[i][j];
            P_Floyd[i][j] = -1;
    }
    for (k = 1; k <= G.n; k++)
        for (i = 1; i <= G.n; i++)
            for (j = 1; j <= G.n; j++)
                if (D_Floyd[i][k] + D_Floyd[k][j] < D_Floyd[i][j])
                {
                    D_Floyd[i][j] = D_Floyd[i][k] + D_Floyd[k][j];
                    P_Floyd[i][j] = k;
                }
}

/*
void Floyd_path(int source, int target)
{
    if(source>G.n||target>G.n)
        ;
    错误，退出
    初始化path数组;
    for (int i = 1; i <= G.n; i++)
        for (int j = 1; j <= G.n; j++)
            path_Floyd[i][j] = 0;

    int pre = P_Floyd[source][target];
    int tmp_target;
    while (pre != -1)
    {
        path_Floyd[pre][target] = 1;
        tmp_target = pre;
        pre = P_Floyd[source][tmp_target];
    }
    path_Floyd[source][tmp_target] = 1;
    //output
    printf("The matrix of the minimal path:\n");
    for (int i = 1; i <= G.n; i++)
    {
        for (int j = i; j <= G.n; j++)
        {
            printf("%d ",path_Floyd[i][j]);
        }
        printf("\n");
    }
    
}
*/

void Floyd_reachable_matrix()
{
    for (int i = 1; i <= G.n; i++)
        for (int j = 1; j <= G.n; j++)
        {
            if (P_Floyd[i][j] = INT_MAX)
                reachable_matrix[i][j] = 1;
        }
    for (int i = 1; i <= G.n; i++)
    {
        for (int j = 1; j <= G.n; j++)
        {
            printf("%d ", reachable_matrix[i][j]);
        }
        printf("\n");
    }
}

void Showmatrix(MTGraph G)
{
    printf("\nVertices:");
    for (int j = 1; j <= G.n; j++)
    {
        printf("%c ", G.vertex[j]);
    }
    printf("\nAdjacency matrix:\n");
    for (int i = 1; i <= G.n; i++)
    {
        for (int j = 1; j <= G.n; j++)
        {
            if (G.edge[i][j] == INT_MAX)
                printf("n ");
            else
                printf("%d ", G.edge[i][j]);
        }
        printf("\n");
    }
}
