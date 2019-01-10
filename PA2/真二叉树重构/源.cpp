
//One Judge, All Accepted!

#include<cstdio>
#include<cstdlib>

#ifndef _OJ_
#include<cassert>
#pragma warning(disable:4996)
#endif // !_OJ_
const int MAX = 4000000;
//����
int PreOrder[MAX], PostOrder[MAX];
int Out[MAX], count = 0, n;

void Rebuild(int startInPre, int endInPre, int startInPost, int endInPost) {  //[start,end)
#ifdef _DEBUG
    assert(endInPost - startInPost == endInPre - startInPre);
#endif // _DEBUG
    if (endInPre - startInPre == 1) {    //Ҷ��
#ifdef _DEBUG
        assert(endInPost - startInPost == 1);
#endif // _DEBUG
        Out[count++] = PreOrder[startInPre];
        return;
    }
#ifdef _DEBUG
    assert(endInPre - startInPre > 2);
#endif // _DEBUG
    //����size>=2
    int LRootInPre = startInPre + 1, RRootInPre, LRootInPost, RRootInPost = endInPost - 2;    //index
    //��ȡ��������
    for (int i = endInPre - 1; i >= startInPre; i--) {
        if (PreOrder[i] == PostOrder[RRootInPost]) {
            RRootInPre = i;
            break;
        }
    }
    for (int i = startInPost; i < endInPost; i++) {
        if (PostOrder[i] == PreOrder[LRootInPre]) {
            LRootInPost = i;
            break;
        }
    }
    Rebuild(LRootInPre, RRootInPre, startInPost, LRootInPost + 1);    //������
    Out[count++] = PreOrder[startInPre];    //root
    Rebuild(RRootInPre, endInPre, LRootInPost + 1, RRootInPost + 1);    //������
}


int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", PreOrder + i);
    for (int i = 0; i < n; i++)
        scanf("%d", PostOrder + i);
    Rebuild(0, n, 0, n);
#ifdef _DEBUG
    assert(count == n);
#endif // _DEBUG
    printf("%d", Out[0]);
    for (int i = 1; i < n; i++) {
        printf(" %d", Out[i]);
    }
#ifndef _OJ_
    system("pause");
#endif // _OJ_
    return 0;
}