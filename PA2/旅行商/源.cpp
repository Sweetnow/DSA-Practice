#include <cstdio>
#ifndef _OJ_
#include <cstdlib>
#pragma warning(disable : 4996)
#endif // !_OJ_

#ifdef NULL
#undef NULL
#endif // NULL

typedef int POINTER;

const int MAX = 1000001;
const int NULL = -1;
int n, m;

struct VERTEX
{
    int count = 1;                     //��� ���� �Ӹõ�������ߵ����Ĵ�ׯ��
    POINTER front = NULL, back = NULL; //�ڽӱ�
    bool isUsed = false;               //����DFS
} vertex[MAX];                         //�±��ǽ��

//���������� Stack
POINTER sorted[MAX];
int top = 0;
void Push(POINTER x)
{
    sorted[top++] = x;
}

//���ڽӱ�
int edge[MAX];       //��¼ָ��Ľ��
POINTER next[MAX];   //������һ���
POINTER trailer = 0; //ָ��δ��ռ�õ�β��

void AddEdge(int out, int in)
{ //����һ����outVertex->inVertex�ı�
    edge[trailer] = in;
    if (vertex[out].front == NULL)
    { //δ��������
        vertex[out].back = vertex[out].front = trailer;
    }
    else
    { //�Ѿ�����������
        next[vertex[out].back] = trailer;
        vertex[out].back = trailer;
    }
    next[trailer] = NULL;
    trailer++;
}

//���������е�DFSģ��
void SortDFS(POINTER now)
{
    vertex[now].isUsed = true;
    POINTER current = vertex[now].front;
    while (current != NULL)
    {
        if (!vertex[edge[current]].isUsed)
        {
            SortDFS(edge[current]);
        }
        current = next[current];
    }
    Push(now);
}

//������Զ���ߵĴ�ׯ��
int CountMax()
{
    int maxNumber = 0;
    for (int i = 0; i < top; i++)
    {
        int maxTmp = 0; //���ڼ�¼��ǰ�������ɴ�Ľ���count���ֵ
        POINTER current = vertex[sorted[i]].front;
        while (current != NULL)
        {
            maxTmp = (maxTmp >= vertex[edge[current]].count ? maxTmp : vertex[edge[current]].count);
            current = next[current];
        }
        vertex[sorted[i]].count += maxTmp;
        maxNumber = (maxNumber >= vertex[sorted[i]].count ? maxNumber : vertex[sorted[i]].count);
    }
    return maxNumber;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int in, out;
        scanf("%d%d", &out, &in);
        AddEdge(out, in);
    }
    //��������
    for (POINTER i = 1; i <= n; i++)
    {
        if (!vertex[i].isUsed)
        {
            SortDFS(i);
        }
    }
    printf("%d\n", CountMax());
#ifndef _OJ_
    system("pause");
#endif // !_OJ_
    return 0;
}