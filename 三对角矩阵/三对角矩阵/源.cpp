#include<cstdio>

#ifdef NATIVE
#pragma warning(disable:4996)
#else
#pragma g++ optimize O3
#endif // NATIVE

#define index_A(i,j) (2*(i)+(j))
#define index_B(i,j) ((i)*(n)+(j))
#define index_X(i,j) ((i)*(n)+(j))

int m, n;
int main()
{
    scanf("%d%d", &m, &n);
    double* A = new double[3 * m], *B = new double[m*n], *X = new double[m*n];
    for (int cnt = 0; cnt < m; ++cnt)
    {
        scanf("%lf", A + index_A(cnt, cnt));
    }
    for (int cnt = 0; cnt < m - 1; ++cnt)
    {
        scanf("%lf", A + index_A(cnt, cnt + 1));
    }
    for (int cnt = 0; cnt < m - 1; ++cnt)
    {
        scanf("%lf", A + index_A(cnt + 1, cnt));
    }
    for (int tmp = 0; tmp < n; ++tmp)
    {
        for (int cnt = 0; cnt < m; ++cnt)
        {
            scanf("%lf", B + index_B(cnt, tmp));
        }
    }
    int pivot_column = 0;
    for (int pivot_line = 0; pivot_line < m; ++pivot_line, ++pivot_column)
    {
        double pivot = A[index_A(pivot_line, pivot_column)];
        //Gauss
        for (int line = pivot_line + 1; line < m && pivot_column >= line - 1; ++line)
        {
            double first = A[index_A(line, pivot_column)];
            if (first != 0)
            {
                for (int column = line - 1; column <= line + 1 && column < m; ++column)
                {
                    A[index_A(line, column)] -= first * A[index_A(pivot_line, column)] / pivot;
                }
                for (int column = 0; column < n; ++column)
                {
                    B[index_B(line, column)] -= first * B[index_B(pivot_line, column)] / pivot;
                }
            }
        }
    }
    for (int column = 0; column < n; ++column)
    {
        X[index_X(m - 1, column)] = B[index_B(m - 1, column)] / A[index_A(m - 1, m - 1)];
        for (int i = m - 2; i >= 0; --i)
        {
            X[index_X(i, column)] = (B[index_B(i, column)] - A[index_A(i, i + 1)] * X[index_X(i + 1, column)]) / A[index_A(i, i)];
        }
        for (int i = 0; i < m; ++i)
        {
            printf("%lf ", X[index_X(i, column)]);
        }
        putchar('\n');
    }
    delete A;
    delete B;
    delete X;
    return 0;
}