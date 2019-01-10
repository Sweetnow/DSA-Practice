#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<memory.h>

#pragma warning(disable:4996)

#define NODE_MAX (65)
#define K_MAX (10)
#define X_MAX (80)  //x in [X_MIN, X_MAX)
#define X_MIN (1)
#define Y_MAX (40)  //y in [Y_MIN, Y_MAX)
#define Y_MIN (1)
#define LOOP_MAX (10)

typedef struct
{
    double x, y;
}node;

int n, k, loop_cnt = 0;
node all[NODE_MAX];
node center[K_MAX];
node next_center[K_MAX];
int group[K_MAX][NODE_MAX];     //save the index of node in all
int group_len[K_MAX] = { 0 };

int main()
{
    srand(time(NULL));
    n = rand() % NODE_MAX;
    //create randomly
    for (int i = 0; i < n; ++i)
    {
        int same = 0;
        double x, y;
        do
        {
            x = rand() % (X_MAX - X_MIN) + X_MIN;
            y = rand() % (Y_MAX - Y_MIN) + Y_MIN;
            for (int index = 0; index < i && !same; ++index)
            {
                same = all[index].x == x && all[index].y == y;
            }
        } while (same);
        all[i].x = x;
        all[i].y = y;
    }
    //choose center points randomly
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        int same = 0;
        int center_index;
        do
        {
            center_index = rand() % n;
            for (int index = 0; index < i && !same; ++index)
            {
                same = center[index].x == all[center_index].x && center[index].y == all[center_index].y;
            }
        } while (same);
        center[i] = all[center_index];
    }
    //refresh center points
    do
    {
        //init
        for (int i = 0; i < k; ++i)
        {
            group_len[i] = 0;
        }
        //choose group
        for (int i = 0; i < n; ++i)
        {
            double min_dst = INFINITY;
            int min_c;
            for (int c = 0; c < k; ++c)
            {
                double dst = sqrt((all[i].x - center[c].x)*(all[i].x - center[c].x) + (all[i].y - center[c].y)*(all[i].y - center[c].y));
                if (dst < min_dst)
                {
                    min_dst = dst;
                    min_c = c;
                }
            }
            group[min_c][group_len[min_c]++] = i;
        }
        //calculate new center
        for (int i = 0; i < k; ++i)
        {
            double sum_x=0, sum_y=0;
            for (int j = 0; j < group_len[i]; ++j)
            {
                sum_x += all[group[i][j]].x;
                sum_y += all[group[i][j]].y;
            }
            next_center[i].x = sum_x / group_len[i];
            next_center[i].y = sum_y / group_len[i];
            printf("group %d:(%lf,%lf)\n", i, next_center[i].x, next_center[i].y);
        }
        memcpy(center, next_center, sizeof(center));
    } while (loop_cnt++<LOOP_MAX);
    system("pause");
    return 0;
}