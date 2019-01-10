#include<cstdio>
#include<cstring>
#ifndef __OJ__
#pragma warning(disable:4996)
#endif // !__OJ__
const size_t MAX_N = 600000;
const size_t MAX_LEN = 40 + 2;
const size_t PRIME = 599999;
const unsigned A = 26;
const unsigned B = 17;

size_t n;
unsigned is_existed[PRIME];
char str_array[PRIME][MAX_LEN];
inline unsigned hash(const char *str)
{
    unsigned result = B;
    while (*str != '\0')
    {
        result *= A;
        result += *str - 'a';
        result %= PRIME;
        ++str;
    }
    return result;
}
unsigned get(unsigned hashcode, const char *str = "", bool is_check = false, bool *pflag = nullptr)
{
    int i = -1;
    bool minus = false;
    int now_hashcode;
    do
    {
        //refresh hashcode
        ++i;
        minus = !minus;
        now_hashcode = hashcode + (minus ? -1 : 1) * i * i;
        now_hashcode %= PRIME;
        if (now_hashcode < 0)
            now_hashcode += PRIME;
        //check whether str appears twice
        if (is_check)
        {
            if (strcmp(str, str_array[now_hashcode]) == 0)
            {
                *pflag = true;
                return now_hashcode;
            }
        }
    } while (is_existed[now_hashcode] != 0);
    return now_hashcode;
}

bool insert_and_check_twice(const char *str)
{
    bool flag = false;
    unsigned index = get(hash(str), str, true, &flag);
    ++is_existed[index];
    if (flag)
    {
        return is_existed[index] == 2;
    }
    else
    {
        strcpy(str_array[index], str);
        return false;
    }
}

int main()
{
    char tmp[MAX_LEN];
    scanf("%u", &n);
    getchar();
    for (size_t i = 0; i < n; ++i)
    {
        fgets(tmp, MAX_LEN, stdin);
        if (insert_and_check_twice(tmp))
        {
            tmp[strlen(tmp) - 1] = '\0';
            puts(tmp);
        }
    }
#ifndef __OJ__
    getchar();
    getchar();
#endif // !__OJ__

    return 0;
}