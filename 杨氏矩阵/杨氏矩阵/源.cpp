#include<cstdio>
#include<climits>
#include<memory.h>
#include<utility>
#include<algorithm>
#define index(a,b) ((a)*max_column+(b))

#ifdef NATIVE
#pragma warning(disable:4996)
#else
#pragma g++ optimize O3
#endif // NATIVE

const int MAX = 1000000;
unsigned int matrix[MAX];
bool is_deleted[MAX];
int indexx = 0;
int N, N1, N2, N3;
int max_column, max_row = 0;
bool is_first = true;
int temp;
int count = 0;
int row_search(unsigned int target, int low, int high)
{
    while (low < high)
    {
        int mid = (high + low) / 2;
        if (matrix[index(0, mid)] <= target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }
    return low - 1 ;
    //if low-1==-1, search failed.
}
//std::pair<int, int> column_search(unsigned int target, int column, int low, int high)
//{
//    while (low < high)
//    {
//        int mid = (high + low) / 2;
//        if (matrix[index(mid, column)] < target)
//        {
//            low = mid + 1;
//        }
//        else
//        {
//            high = mid;
//        }
//    }
//    return { low,column };
//    //if low==max_row, search failed.
//}
std::pair<int, int> my_search(unsigned int target)
{
    std::pair<int, int>now{ 0,max_column - 1 };
    while (matrix[index(now.first, now.second)] != target)
    {
        if (matrix[index(now.first, now.second)] > target)
        {
            now.second -= 1;
        }
        else
        {
            now.first += 1;
        }
        if (now.second < 0 || now.first >= max_row)
            return { -1,-1 };
        /*now = row_search(target, now.first, 0, now.second + 1);
        if (now.second < 0)
            return { -1,-1 };
        now = column_search(target, now.second, now.first, max_row);
        if (now.first >= max_row)
            return { -1,-1 };*/
    }
    if (matrix[index(now.first, now.second)] == target)
        return now;
    else
        return { -1,-1 };
}

int main()
{
    memset(matrix, UINT_MAX, sizeof(matrix));
    scanf("%d%d%d%d", &N, &N1, &N2, &N3);
    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &temp);
        if (temp == -1)
        {
            if (is_first)
            {
                is_first = false;
                max_column = count;
            }
            else
            {
                indexx += max_column - count;
            }
            ++max_row;
            count = 0;
        }
        else
        {
            ++count;
            matrix[indexx++] = temp;
        }
    }
    for (int i = 0; i < N1; ++i)
    {
        scanf("%d", &temp);
        //binary search
        auto result = my_search(temp);
        printf(i == 0 ? "%d %d" : " %d %d", result.first, result.second);
    }
    putchar('\n');
    for (int i = 0; i < N2; ++i)
    {
        scanf("%d", &temp);
        matrix[indexx++] = temp;
    }
    std::sort(matrix, matrix + max_column * max_row + N2);
    for (int i = 0; matrix[i] < UINT_MAX; ++i)
    {
        printf("%d ", matrix[i]);
    }
    printf("%d\n", -1);
    int now_N = N + N2;
    for (int i = 0; i < N3; ++i)
    {
        scanf("%d", &temp);
        is_deleted[row_search(temp, 0, now_N)] = true;
    }
    for (int i = 0; matrix[i] < UINT_MAX; ++i)
    {
        if (!is_deleted[i])
            printf("%d ", matrix[i]);
    }
    printf("%d\n", -1);
    return 0;
}