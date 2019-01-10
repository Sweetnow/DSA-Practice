/*
#include<iostream>

template<int N>
class SeqList
{
public:
    int length = 0;
    int list[N];

    void append(int n)
    {
        list[length++] = n;
    }
};

template<int N>
void inverseSeqList(SeqList<N> &L)
{
    for (int i = 0; i < L.length / 2; i++)
    {
        int tmp = L.list[i];
        L.list[i] = L.list[L.length - 1 - i];
        L.list[L.length - 1 - i] = tmp;
    }
}


int main()
{
    SeqList<10> a;
    for (size_t i = 0; i < 5; i++)
    {
        a.append(i);
    }
    inverseSeqList(a);
    return 0;
}
*/