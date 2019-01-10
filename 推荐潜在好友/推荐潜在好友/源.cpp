#include<cstdio>
#include<vector>
#include<algorithm>
#include<cctype>
#ifdef NATIVE
#pragma warning(disable:4996)
#else
#pragma g++ optimize O3
#endif // NATIVE

using std::vector;
const int MAX = 3000;
const int BYTE = 8;
int N, K, U;

class bitmap
{
public:
    bitmap()
    {
        for (int i = 0; i < MAX / BYTE + 1; ++i)
        {
            _data[i] = 0;
        }
    }
    ~bitmap()
    {
    }
    void set(int n)
    {
        _data[n / BYTE] |= 1 << (n % BYTE);
    }
    bool test(int n)
    {
        return _data[n / BYTE] & (1 << (n % BYTE));
    }

private:
    unsigned char _data[MAX / BYTE + 1];
};

vector<std::pair<int, int>>result;  //<count,number>
bitmap data[MAX];

bool cmp(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    return a.first > b.first || (a.first == b.first&&a.second < b.second);
}


int main()
{
    scanf("%d%d%d", &N, &K, &U);
    char* tmp_s = new char[2 * N + 5];
    fgets(tmp_s, 2 * N + 5, stdin);     // \r \n
    for (int i = 0; i < N; i++)
    {
        fgets(tmp_s, 2 * N + 5, stdin);
        int c = -1;
        int j = 0;
        while (tmp_s[++c] != '\0')
        {
            if (tmp_s[c] == '1')
            {
                data[i].set(j);
                ++j;
            }
            else if (tmp_s[c] == '0')
            {
                ++j;
            }
        }
    }
    delete tmp_s;
    for (int i = 0; i < N; ++i)
    {
        if (i == U)
            continue;
        if (!data[U].test(i))
        {
            //not friend
            int count = 0;
            for (int j = 0; j < N; ++j)
            {
                count += (data[U].test(j) && data[i].test(j));
            }
            if (count >= K)
            {
                result.push_back({ count,i });
            }
        }
    }
    std::sort(result.begin(), result.end(), cmp);
    for (auto& one : result)
    {
        printf("%d ", one.second);
    }
#ifdef NATIVE
    getchar(); getchar();
#endif // NATIVE

    return 0;
}