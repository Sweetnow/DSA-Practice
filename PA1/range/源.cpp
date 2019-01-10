#include<cstdio>
#include<cstdlib>
#pragma warning(disable:4996)
#define MAX (500005)
int tmp[MAX];    //�����ռ�
int buf[MAX];    //���ռ�
void merge(int buf[], int start, int mid, int end) {    //�ϲ�[start,mid)��[mid,end)
    for (int i = 0, j = start; j < mid; i++, j++)
        tmp[i] = buf[j];
    for (int i = 0, j = mid, in = start; i < mid - start;) {    //ʹ�õ�ָ����i,j,����i��Ը����ռ䣬���е�i==mid-start��β��j��Ժ��Σ����е�j==end��β��д��ָ��ʹ��in
        if (j < end && buf[j] < tmp[i])
            buf[in++] = buf[j++];
        if (!(j < end) || tmp[i] <= buf[j])
            buf[in++] = tmp[i++];
    }
}
void mergeSort(int buf[], int start, int end) {    //����Χ[start,end)
    if (end - start < 2)
        return;
    int mid = (start + end) / 2;
    mergeSort(buf, start, mid);
    mergeSort(buf, mid, end);
    merge(buf, start, mid, end);
}
int binarySearch(int buf[], int target, int start, int end) {    //��buf��[start,end)�ж��ֲ���target
    int mid;
    while (end > start) {
        mid = (start + end) / 2;
        if (target < buf[mid])
            end = mid;
        else
            start = mid + 1;
    }
    return start - 1;
}
int main() {
    int n, m, a, b, index_a, index_b;    //n������m��ѯ����,a��߽�,b�ұ߽�
    scanf("%d%d", &n, &m);
    //unsigned *buf = new unsigned[n];
    //tmp = new unsigned[n / 2 + 1];
    for (int i = 0; i < n; i++) {
        scanf("%d",&buf[i]);
    }
    //sort O(nlogn)
    mergeSort(buf, 0, n);
    //binarySearch O(mlogn)
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        index_a = binarySearch(buf, a, 0, n);
        index_b = binarySearch(buf, b, 0, n);
        if (index_a >= 0 && buf[index_a] == a)
            printf("%d\n", index_b - index_a + 1);
        else
            printf("%d\n", index_b - index_a);
    }
    //delete[]tmp;
    //delete[]buf;
    return 0;
}