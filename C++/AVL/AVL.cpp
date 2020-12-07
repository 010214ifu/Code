#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

class AVL
{
private:
    struct Node
    {
        int Data, Height;
        Node *Lchild, *Rchild;
        Node()
        {
            Lchild = NULL;
            Rchild = NULL;
            Height = 0;
        }
    };
    typedef Node * NodeAVL;
    int Height(NodeAVL x)
    {
        if(x == NULL)
            return 0;
        else
            return x->Height;
    }
    void UpdateHeight(NodeAVL x)
    {
        if(x == NULL)
            return;
        x->Height = max(Height(x->Lchild), Height(x->Rchild)) + 1;
    }
    NodeAVL LL_rotate(NodeAVL x)
    {
        NodeAVL temp = x->Lchild->Rchild;
        NodeAVL newroot = x->Lchild;
        newroot->Rchild = x;
        x->Lchild = temp;
        UpdateHeight(x->Rchild);
        UpdateHeight(x);
        return newroot;
    }
    NodeAVL RR_rotate(NodeAVL x)
    {
        NodeAVL temp = x->Rchild->Lchild;
        NodeAVL newroot = x->Rchild;
        newroot->Lchild = x;
        x->Rchild = temp;
        UpdateHeight(x->Lchild);
        UpdateHeight(x);
        return newroot;
    }
    NodeAVL LR_rotate(NodeAVL x)
    {
        x->Lchild = RR_rotate(x->Lchild);
        return LL_rotate(x);
    }
    NodeAVL RL_rotate(NodeAVL x)
    {
        x->Rchild = LL_rotate(x->Rchild);
        return RR_rotate(x);
    }
    int DeleteMin(NodeAVL &x)
    {
        if (x->Lchild == NULL)
        {
            int temp = x->Data;
            x = x->Rchild;
            return temp;
        }
        else
        {
            int res;
            res = DeleteMin(x->Lchild);
            UpdateHeight(x);
            return res;
        }
    }
    void Rotating(NodeAVL &x)
    {
        if(Height(x->Lchild) == Height(x->Rchild) + 2)
        {
            if(Height(x->Lchild->Lchild) > Height(x->Lchild->Rchild))
                x = LL_rotate(x), cout << "LL\n";
            else
                x = LR_rotate(x), cout << "LR\n";
        }
        else if(Height(x->Rchild) == Height(x->Lchild) + 2)
        {
            if(Height(x->Rchild->Rchild) > Height(x->Rchild->Lchild))
                x = RR_rotate(x), cout << "RR\n";
            else
                x = RL_rotate(x), cout << "RL\n";
        }
        UpdateHeight(x);
    }
    

public:
    NodeAVL Root;
    void Insert(NodeAVL &x, int Data)
    {
        if(x == NULL)
        {
            x = new Node;
            x->Data = Data;
            x->Height = 1;
            return;
        }
        if(x->Data > Data)
            Insert(x->Lchild, Data);
        else if(x->Data < Data)
            Insert(x->Rchild, Data);
        else //==
            return;
        Rotating(x);
    }
    int Delete(NodeAVL &x, int Data)
    {
        if (x == NULL)
            return INT32_MIN;
        else
        {
            int Res;
            if (x->Data > Data)
                Res = Delete(x->Lchild, Data);
            else if (x->Data < Data)
                Res = Delete(x->Rchild, Data);
            else
            {
                int temp = x->Data;
                if(x->Lchild == NULL)
                    x = x->Rchild;
                else if(x->Rchild == NULL)
                    x = x->Lchild;
                else
                    x->Data = DeleteMin(x->Rchild);
                UpdateHeight(x);
                return temp;
            }
            Rotating(x);
            return Res;
        }
    }
    int Search(NodeAVL &x, int Data)
    {
        if ((Data < x->Data && x->Lchild == NULL) || (Data > x->Data && x->Rchild == NULL))
            return INT32_MIN;
        if (x->Data == Data)
            return Data;
        else if(x->Data > Data)
            return Search(x->Lchild, Data);
        else
            return Search(x->Rchild, Data);
    }
    void Ranking(NodeAVL x)
    {
        if (x == NULL)
            return;
        Ranking(x->Lchild);
        cout << x->Data << " ";
        Ranking(x->Rchild);
    }
};

AVL Tree;
int main()
{
    int num, x, s;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> num;
    for (int i = 1; i <= num; i++)
    {
        cin >> x;
        Tree.Insert(Tree.Root, x);
    }
    freopen("CON", "r", stdin);
    freopen("CON", "w", stdout);
    while (1)
    {
        int cho;
        cout << "------------------------\n";
        cout << "---     0. Quit      ---\n";
        cout << "---    1. Insert     ---\n";
        cout << "---    2. Delete     ---\n";
        cout << "---    3. Search     ---\n";
        cout << "---     4. Rank      ---\n";
        cout << "------------------------\n";
        cout << "Which do you wanna choose?\n";
        fflush(stdin);
        scanf("%d", &cho);
        if(cho == 0)
            break;
        else if(cho == 1)
        {
            scanf("%d", &x);
            Tree.Insert(Tree.Root, x);
        }
        else if(cho == 2)
        {
            scanf("%d", &x);
            s = Tree.Delete(Tree.Root, x);
            if (s == INT32_MIN)
                cout << "Don't Exist.\n";
        }
        else if (cho == 3)
        {
            scanf("%d", &x);
            s = Tree.Search(Tree.Root, x);
            if (s == x)
                cout << "Search Successfully!\n";
            else
                cout << "Don't exist!\n";
        }
        else if (cho == 4)
        {
            Tree.Ranking(Tree.Root);
            cout << "\n";
        }
        else
            cout << "Wrong!\n";
    }
    return 0;
}