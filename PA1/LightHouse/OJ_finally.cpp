#include<cstdio>
#include<cstdlib>
#pragma warning(disable:4996)
const int MAX = 4000000;
using namespace std;
struct Pos {
    int x, y;
}allPos[MAX];
int tmpY[MAX];
int Y[MAX];
unsigned long long count = 0;

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

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &allPos[i].x, &allPos[i].y);
    qsort(allPos, n, sizeof(Pos), cmpPos);
    for (int i = 0; i < n; i++)
        Y[i] = allPos[i].y;
    countInside(0, n);
    printf("%llu", count);
    return 0;
}