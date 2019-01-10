#ifdef NATIVE
#pragma warning(disable:4996)
#else
#pragma g++ optimize O3
#endif 

#include<cstdio>
#include<stack>

using std::stack;

struct edge
{   //[l,r)
    int l;
    int r;
};

const int MAX = 11000;
int N, K;
int buffer[MAX];
edge e[2] = { {0,0},{0,0} };

inline int max(int a, int b)
{
    if (a < b)
        return b;
    else
        return a;
}
//begin and end are indexs of buf [begin, end)
int get_max_rectamgle(int buf[], int begin, int end, int index)
{
    stack<int> s;
    int max_area = 0;
    int i = begin;
    while (i < end)
    {
        if (s.empty() || buf[i] >= buf[s.top()])
        {
            s.push(i++);
        }
        else
        {
            int last = s.top();
            s.pop();
            if (s.empty() && max_area < buf[last] * (i - begin))
            {
                max_area = buf[last] * (i - begin);
                e[index] = { begin,i };
            }
            else if (!s.empty() && max_area < buf[last] * (i - s.top() - 1))
            {
                max_area = buf[last] * (i - s.top() - 1);
                e[index] = { s.top() + 1,i };
            }
        }
    }
    //i==end
    int last;
    do
    {
        last = s.top();
        s.pop();
        if (s.empty() && max_area < buf[last] * (i - begin))
        {
            max_area = buf[last] * (i - begin);
            e[index] = { begin,i };
        }
        else if (!s.empty() && max_area < buf[last] * (i - s.top() - 1))
        {
            max_area = buf[last] * (i - s.top() - 1);
            e[index] = { s.top() + 1,i };
        }
    } while (!s.empty());
    return max_area;
}

int main()
{
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; ++i)
    {
        scanf("%d", buffer + i);
    }
    int max_area = 0;
    for (int first_end = 1; first_end < N - K; )
    {
        int a = get_max_rectamgle(buffer, 0, first_end, 0);
        int b = get_max_rectamgle(buffer, first_end + K, N, 1);
        if (max_area < a + b)
        {
            max_area = a + b;
            first_end = e[1].l - K;
        }
        else
        {
            ++first_end;
        }
    }
    printf("%d", max_area);
    return 0;
}