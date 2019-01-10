#define NATIVE
#include<cstdio>
#ifdef NATIVE
#pragma warning(disable:4996)
#else
#pragma g++ optimize O3
#endif // NATIVE

#define GET_BIT(byte,n) (((byte)>>(n)) & 1)

struct matrix
{
    int data[2][2];
    matrix(int left_up = 0, int right_up = 0, int left_down = 0, int right_down = 0)
    {
        data[0][0] = left_up;
        data[0][1] = right_up;
        data[1][0] = left_down;
        data[1][1] = right_down;
    }
    matrix(const matrix &a)
    {
        for (size_t i = 0; i < 2; i++)
        {
            for (size_t j = 0; j < 2; j++)
            {
                data[i][j] = a.data[i][j];
            }
        }
    }
};
matrix operator*(const matrix &left, const matrix &right)
{
    return
    {
    left.data[0][0] * right.data[0][0] + left.data[0][1] * right.data[1][0],
    left.data[0][0] * right.data[0][1] + left.data[0][1] * right.data[1][1],
    left.data[1][0] * right.data[0][0] + left.data[1][1] * right.data[1][0],
    left.data[1][0] * right.data[0][1] + left.data[1][1] * right.data[1][1]
    };
}
matrix &operator%=(matrix &left, int mod)
{
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            left.data[i][j] %= mod;
        }
    }
    return left;
}
matrix log[32];
const matrix base{ 1,1,1,0 };
const int PRIME = 9973;
int n = 0;
int main()
{
    scanf("%d", &n);
    log[0] = base;
    for (size_t i = 1; i < 32; i++)
    {
        log[i] = log[i - 1] * log[i - 1];
        log[i] %= PRIME;
    }
    for (int i = 0; i < n; i++)
    {
        int nth;
        scanf("%d", &nth);
        nth -= 1;
        if (nth == -1)
        {
            printf("%d\n", 0);
        }
        else if (nth == 0)
        {
            printf("%d\n", 1);
        }
        else
        {
            matrix tmp = base;
            for (size_t i = 0; i < 31; i++)
            {
                if (GET_BIT(nth, i) == 1)
                {
                    tmp = tmp * log[i];
                    tmp %= PRIME;
                }
            }
            printf("%d\n", tmp.data[0][1]);
        }
    }
    return 0;
}