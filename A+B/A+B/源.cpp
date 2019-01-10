#include<cstdio>
#include<cstring>
//#pragma warning(disable:4996)
const int MAX = 1000;
char a[MAX], b[MAX], result[MAX];
int main()
{
    char tmp = 0;   //½øÎ»
    char *plong = nullptr, *pshort = nullptr;
    size_t i;
    scanf("%s %s", a, b);
    size_t len_of_long = strlen(a), len_of_short = strlen(b);
    if (len_of_long >= len_of_short)
    {
        plong = a;
        pshort = b;
    }
    else
    {
        size_t tmp;
        plong = b;
        pshort = a;
        tmp = len_of_long;
        len_of_long = len_of_short;
        len_of_short = tmp;
    }
    plong = plong + len_of_long - 1;
    pshort = pshort + len_of_short - 1;
    for (i = MAX - 2; i >= MAX - len_of_short - 1; --i, --plong, --pshort)
    {
        result[i] = (tmp + *plong - '0' + *pshort - '0') % 10;
        tmp = (tmp + *plong - '0' + *pshort - '0') / 10;
    }
    pshort = nullptr;
    for (int range = len_of_short + 1; range <= len_of_long; --i, range++, --plong)
    {
        result[i] = (tmp + *plong - '0') % 10;
        tmp = (tmp + *plong - '0') / 10;
    }
    if (tmp > 0)
    {
        result[i--] = tmp;
    }
    for (size_t index = i + 1; index < MAX - 1; index++)
    {
        result[index] += '0';
    }
    while (result[i + 1] == '0')
        ++i;
    printf("%s", result + i + 1);
    //getchar();
    //getchar();

    return 0;
}