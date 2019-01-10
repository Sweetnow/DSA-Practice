#define NATIVE
#include<cstdio>
#include<algorithm>
//#include<stack>
#ifdef NATIVE
#pragma warning(disable:4996)
#else
#pragma g++ optimize O3
#endif

template<typename T, int SIZE>
class stack
{
public:
    bool push(const T& x)
    {
        if (_index < SIZE)
        {
            _container[_index++] = x;
            return true;
        }
        else
        {
            return false;
        }
    }
    void pop()
    {
        if (_index > 0)
        {
            --_index;
        }
    }
    T top()
    {
        if (_index > 0)
        {
            return _container[_index - 1];
        }
        else
        {
            return T();
        }
    }
    bool empty()
    {
        return _index == 0;
    }
private:
    T _container[SIZE];
    int _index = 0;
};

int N;
int height[100];
struct result
{
    int container[2][50];  //第0行较矮
    int size[2] = { 0,0 };
    int now = 0;
    result() {}
    result(const result &right)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                container[i][j] = right.container[i][j];
            }
            size[i] = right.size[i];
        }
        now = right.now;
    }
    result &operator=(const result &right)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                container[i][j] = right.container[i][j];
            }
            size[i] = right.size[i];
        }
        now = right.now;
        return *this;
    }
    void push(bool row)
    {
        container[row][size[row]++] = height[now++];
    }
    void pop(bool row)
    {
        --now;
        --size[row];
    }
};
int count = 0;
stack<result,205> s; //0表示此操作为在0行填入，1表示在1行填入
int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", height + i);
    }
    std::sort(height, height + N);
    result now_result;
    now_result.push(0);
    s.push(now_result);
    while (!s.empty())
    {
        now_result = s.top();
        s.pop();
        if (now_result.size[0] == N / 2 && now_result.size[1] == N / 2)
        {
            //print
            printf("%d", now_result.container[0][0]);
            for (int i = 1; i < N/2; i++)
            {
                printf(" %d", now_result.container[0][i]);
            }
            for (int i = 0; i < N / 2; i++)
            {
                printf(" %d", now_result.container[1][i]);
            }
            putchar('\n');
            ++count;
        }
        else if (now_result.size[0] == N / 2)
        {
            //row 0 is full
            now_result.push(1);
            s.push(now_result);
        }
        else if (now_result.size[0] == now_result.size[1])
        {
            now_result.push(0);
            s.push(now_result);
        }
        else if (now_result.size[0] > now_result.size[1])
        {
            now_result.push(1);
            s.push(now_result);
            now_result.pop(1);
            now_result.push(0);
            s.push(now_result);
        }
    }
    printf("%d", count);
#ifdef NATIVE
    getchar();
    getchar();
#endif // NATIVE

    return 0;
}