#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
//INT_MAX  INT_MIN
#include<stdbool.h>
#define MAX_VERTEX 100





typedef struct
{
    char vertex[MAX_VERTEX];//顶点信息
    int edge[MAX_VERTEX+1][MAX_VERTEX+1];//边信息
    int n,e;
}MTGraph;

MTGraph G;
int D[MAX_VERTEX + 1];
int P[MAX_VERTEX + 1];
bool S[MAX_VERTEX + 1];

//邻接矩阵存储结构有向图建立
void CreateGraph_matrix();
//最小值
int MinCost();
//Dijkstra算法
void Dijkstra();
//Floyd算法
void Floyd();
//展示图
void Showmatrix(MTGraph G);

int main()
{
    
    return 0;
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

int MinCost()
{
    return;
}

void Dijkstra(int source)
{
    int i, v, w, sum;
    for (i = 1; i <= G.n; i++)
    {
        D[i] = G.edge[source][i];
        S[i] = false;
    }
    S[source] = true;
    for (i = 1; i < G.n; i++)
    {
        w = MinCost();
        S[w] = true;
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
