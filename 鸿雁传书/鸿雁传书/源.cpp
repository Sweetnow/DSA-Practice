#include<cstdio>
#include<string>
#include<map>
#include<algorithm>
#include<vector>

#ifdef NATIVE
#pragma warning(disable:4996)
#else
#pragma g++ optimize O3
#endif // NATIVE

using std::vector;
using std::multimap;
using std::string;

const int MAX = 300000;
int N;
string code[MAX];
unsigned long long num[MAX];
multimap<unsigned long long, vector<int>> tree;

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
    {
        unsigned long long cnt;
        scanf("%d", &cnt);
        num[i] = cnt;
        tree.emplace(std::pair<unsigned long long, vector<int>>(cnt, { i }));
    }
    if (N == 1)
    {
        printf("1\n0\n");
        return 0;
    }
    while (tree.size() > 1)
    {
        auto a = *tree.cbegin();
        tree.erase(tree.cbegin());
        auto b = *tree.cbegin();
        tree.erase(tree.cbegin());
        //merge
        for (auto i : a.second)
        {
            code[i] = '0' + code[i];
        }
        for (auto i : b.second)
        {
            code[i] = '1' + code[i];
        }
        a.second.insert(a.second.end(), b.second.begin(), b.second.end());
        tree.emplace(std::pair<unsigned long long, vector<int>>(a.first + b.first, a.second));
    }
    //average
    double sum = 0;
    unsigned long long num_sum = 0;
    for (int i = 0; i < N; ++i)
    {
        num_sum += num[i];
        sum += code[i].size() * num[i];
    }
    printf("%.6lf\n", sum / num_sum);
    for (int i = 0; i < N; ++i)
    {
        printf("%s\n", code[i].data());
    }
#ifdef NATIVE
    getchar();
    getchar();
#endif // NATIVE

    return 0;
}