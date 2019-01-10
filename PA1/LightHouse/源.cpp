#include<cstdio>
#include<cstdlib>
#include<algorithm>
#pragma warning(disable:4996)
const int MAX = 4000000;
using std::find;
struct Pos {
    int x, y;
}allPos[MAX];
int tmpY[MAX];
int Y[MAX];
unsigned long long count = 0;
#define grid_test allPos
int n;
int cmpPos(const void* a, const void* b) {
    return ((const Pos*)a)->x - ((const Pos*)b)->x;
}
void countBetween(int start, int mid, int end) {
    for (int i = 0, j = start; i < mid - start; i++, j++)
        tmpY[i] = Y[j];
    int i = 0, j = mid;
    for (int in = start; i < mid - start;) {    //使用的指针有i,j,其中i针对辅助空间，运行到i==mid-start结尾，j针对后半段，运行到j==end结尾，写入指针使用in
        if (j < end && Y[j] <= tmpY[i]) {
            count += i;
            Y[in++] = Y[j++];
        }
        if (!(j < end) || tmpY[i] < Y[j])
            Y[in++] = tmpY[i++];
    }
    if (i == mid - start || j != end) {
        count += i * (end - j);
    }
}

void countInside(int start, int end) {
    if (end - start < 2)
        return;
    int mid = (end + start) >> 1;
    countInside(start, mid);
    countInside(mid, end);
    countBetween(start, mid, end);
}

bool operator==(const Pos& a, const Pos&b) {
    return a.x == b.x || a.y == b.y;
}





int n_test, grid_x[400000], grid_y[400000];
//若存在，返回-1，不存在，返回插入点
int judge(int *p, int n, int lo, int hi) {
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        n < p[mid] ? hi = mid : lo = mid + 1;
    }
    if (lo&&p[lo - 1] == n) return -1;
    return lo;
}

void theSort(int *vi, int location, int up) {
    int tem = vi[up];
    while (location < up) {
        vi[up] = vi[up - 1];
        up--;
    }
    vi[location] = tem;
}

void getrand() {

    int base_number = 0;
    for (int i = 0; i < n; i++) {
        if (i % 10000 == 9999)
            base_number += 10000;
        while (true) {
            int location;
            grid_x[i] = rand() % 1000000 + base_number;
            if ((location = judge(grid_x, grid_x[i], 0, i)) == -1)
                continue;
            grid_test[i].x = grid_x[i];
            theSort(grid_x, location, i);
            break;
        }
        while (true) {
            int location;
            grid_y[i] = rand() % 10000000 + base_number;
            if ((location = judge(grid_y, grid_y[i], 0, i)) == -1)
                continue;
            grid_test[i].y = grid_y[i];
            theSort(grid_y, location, i);
            break;
        }
    }
}





int main() {
    for (int sand = 0; sand < 100; sand++) {


        int flag = 0;//重复数
        count = 0;
        srand(sand);
        n = 100000;
        // scanf("%d", &n);
        getrand();
        //for (int i = 0; i < n; i++)
            //scanf("%d%d", &allPos[i].x, &allPos[i].y);
        qsort(allPos, n, sizeof(Pos), cmpPos);
        for (int i = 0; i < n; i++)
            Y[i] = allPos[i].y;
        countInside(0, n);
        printf("%llu sand:%d\n", count, sand);
        system("pause");
    }
    return 0;
}