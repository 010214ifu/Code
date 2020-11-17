#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
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
int reachable_matrix[MAX_VERTEX+1][MAX_VERTEX+1];
int path_Floyd[MAX_VERTEX+1][MAX_VERTEX+1];

//创建空堆
void MakeNullHeap();
//判断空堆
bool HeapEmpty();
//判断满堆
bool HeapFull();
//初始化堆
void HeapInit(int source);
//堆插入
void Insert(int sub, int path_length);
//堆删除任意位置元素，返回角标
int DeleteData(int k);

//栈
STACK MAKENULL_STACK( );
void PUSH(STACK S, int k);
int POP(STACK S);

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
/*
Dijkstra最短路径长度和最短路径
Floyd最短距离矩阵和最短路径矩阵，任意两个顶点最短路径长度和最短路径
每个顶点到指定顶点c最短路径
u到v和v到u最短路径
Floyd可达矩阵
*/

int main()
{
    CreateGraph_matrix();
    Floyd();
    int source, target, cho = 1;
    while (cho != 0)
    {
        system("cls");
        printf("----------------------------------------------\n");
        printf("--                   0.Quit                 --\n");
        printf("--    1.Dijkstra from one point to others   --\n");
        printf("--  2.Floyd matrix of the shortest distance --\n");
        printf("--   3.Floyd pathes between any two points  --\n");
        printf("--  4.Pathes from every point to given one  --\n");
        printf("--             5.reachable matrix           --\n");
        printf("--         6.Pathes between two points      --\n");
        printf("----------------------------------------------\n");
        printf("Which do you wanna choose? ");
        scanf("%d", &cho);
        switch (cho)
        {
        case 0://Quit
            printf("Quit successfully!\n");
            break;
        case 1:
            printf("Input source point:");
            scanf("%d", &source);
            Dijkstra(source);
            for (int i = 1; i <= G.n; i++)
                Dijkstra_path(source, i);
            system("pause");
            break;
        case 2:
            printf("\nMatrix of the shortest distance:\n");
            for (int i = 1; i <= G.n; i++)
            {
                for (int j = 1; j <= G.n; j++)
                {
                    if (D_Floyd[i][j] != INT_MAX)
                        printf("%d ", D_Floyd[i][j]);
                    else
                        printf("s ");
                }
                printf("\n");
            }
            system("pause");
            break;
        case 3:
            printf("\nPathes between any two vertices:\n");
            for (int i = 1; i <= G.n; i++)
                for (int j = 1; j <= G.n; j++)
                    if(D_Floyd[i][j]!=INT_MAX)
                    {
                        printf("%c to %c: %c", G.vertex[i],G.vertex[j],G.vertex[i]);
                        Floyd_path(i,j);
                        printf("\n");
                    }
            system("pause");
            break;
        case 4:
            printf("Input target point:");
            scanf("%d", &target);
            for (int i = 1; i <= G.n; i++)
            {
                if(D_Floyd[i][target]!=INT_MAX)
                {
                    printf("%c to %c: %c", G.vertex[i],G.vertex[target],G.vertex[i]);
                    Floyd_path(i,target);
                    printf("\n");
                }
            }
                system("pause");
            break;
        case 5:
            printf("\nReachable matrix:\n");
            Floyd_reachable_matrix();
            system("pause");
            break;
        case 6:
            printf("Input two points:");
            scanf("%d %d", &source, &target);
            if (D_Floyd[source][target] != INT_MAX)
            {
                printf("%c to %c: %c", G.vertex[source], G.vertex[target], G.vertex[source]);
                Floyd_path(source, target);
                printf("\n");
            }
            else
                printf("%c cannot reach %c.\n", G.vertex[source], G.vertex[target]);
            if (D_Floyd[target][source] != INT_MAX)
            {
                printf("%c to %c: %c", G.vertex[target], G.vertex[source], G.vertex[target]);
                Floyd_path(target, source);
                printf("\n");
            }
            else
                printf("%c cannot reach %c.\n", G.vertex[target], G.vertex[source]);
            system("pause");
            break;
        default:
            printf("Wrong Choice! Choose again.\n");
            system("pause");
            break;
        }
    }
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
void HeapInit(int source)
{
    for (int i = 1; i <= G.n; i++)
        if (i != source)
            Insert(i, D_SPF[i]);
}

void Insert(int sub, int path_length)
{
    int i;
    if(!HeapFull())
    {
        i = Min_Heap.n + 1;
        while (i != 1 && path_length < Min_Heap.data[i / 2].path_length)
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
    int parent = k, child = 2 * k, min;
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
    getchar();
    for (i = 1; i <= G.n; i++)
    {
        scanf("%c", &G.vertex[i]);
        getchar();
        for (j = 1; j <= G.n; j++) //初始化边表
        {
            G.edge[i][j] = INT_MAX;
        }
    }
    for (i = 1; i <= G.e; i++)
    {
        scanf("%d %d %d", &head, &tail, &weight);
        G.edge[head][tail] = weight;
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
        P_SPF[i] = source;
    }
    S_SPF[source] = true;
    MakeNullHeap();
    HeapInit(source);
    for (i = 1; i < G.n; i++)
    {
        w = DeleteData(1);
        S_SPF[w] = true;
        for ( v = 1; v <= Min_Heap.n; v++)
        {
            if (G.edge[w][Min_Heap.data[v].sub] == INT_MAX || D_SPF[w] == INT_MAX)
                sum = INT_MAX;
            else
                sum = G.edge[w][Min_Heap.data[v].sub] + D_SPF[w];
            if (sum < D_SPF[Min_Heap.data[v].sub])
            {
                D_SPF[Min_Heap.data[v].sub] = sum;
                t = DeleteData(v);
                Insert(t, sum);
                P_SPF[t] = w;
            }
        }
    }
}
void Dijkstra_path(int source, int target)
{
    if (D_SPF[target] == INT_MAX || source == target)
    {
        //printf("\n%c have no path to %c.",G.vertex[source],G.vertex[target]);
        return;
    }
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
    printf("\n%c to %c: %c",G.vertex[source],G.vertex[target], G.vertex[pre]);
    while (s->next != NULL)
    {
        printf("-->%c", G.vertex[POP(s)]);
    }

}

void Floyd()
{
    int i, j, k, sum;
    for ( i = 1; i <= G.n; i++)
        for (j = 1; j <= G.n; j++)
        {
            D_Floyd[i][j] = G.edge[i][j];
            P_Floyd[i][j] = -1;
        }
    for (k = 1; k <= G.n; k++)
        for (i = 1; i <= G.n; i++)
            for (j = 1; j <= G.n; j++)
            {
                if (i != j)
                {
                    if (D_Floyd[i][k] == INT_MAX || D_Floyd[k][j] == INT_MAX)
                        sum = INT_MAX;
                    else
                        sum = D_Floyd[i][k] + D_Floyd[k][j];
                    if (sum < D_Floyd[i][j])
                    {
                        D_Floyd[i][j] = sum;
                        P_Floyd[i][j] = k;
                    }
                } 
            }
}
void Floyd_path(int source, int target)
{
    if (D_Floyd[source][target] == INT_MAX)
    {
        printf("%c cannot reach %c.", G.vertex[source], G.vertex[target]);
        return;
    }
    if (source > G.n || target > G.n)
    {
        //printf("Wrong.\n");
        return;
    }
    int k = P_Floyd[source][target];
    if (k != -1)
    {
        Floyd_path(source, k);
        Floyd_path(k, target);
    }
    else
        printf("-->%c", G.vertex[target]);
}
void Floyd_reachable_matrix()
{
    for (int i = 1; i <= G.n; i++)
        for (int j = 1; j <= G.n; j++)
        {
            if (D_Floyd[i][j] != INT_MAX || i == j)
                reachable_matrix[i][j] = 1;
            else if (D_Floyd[i][j] == INT_MAX)
                reachable_matrix[i][j] = 0;
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
