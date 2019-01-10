#include <string>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
int *create_next(string p)
{
    //only kmp
    int *next = new int[p.size()];
    next[0] = 0;
    int i = 0;
    int j = 1;
    while (j < p.size())
    {
        if (p[i] == p[j])
        {
            next[j++] = ++i;
        }
        else if (i > 0)
        {
            i = next[i - 1];
        }
        else
        {
            next[j++] = 0;
        }
    }
    return next;
}
// int * create_next(string p)
// {
//     //kmp with bad word
//     int * next = new int[p.size()];
//     next[0] = 0;
//     int i = 0;
//     int j = 1;
//     while (j < p.size() - 1)
//     {
//         if (p[i] == p[j])
//         {
//             ++i;
//             next[j] = (p[j + 1] == p[i] ? next[i - 1] : i);
//             ++j;
//         }
//         else if (i > 0)
//         {
//             i = next[i - 1];
//         }
//         else
//         {
//             next[j++] = 0;
//         }
//     }
//     return next;
// }

int kmp_and_display(string raw, string p)
{
    int cnt = 0;
    int *next = create_next(p);
    int i = 0;
    int j = 0;
    while (i < raw.size())
    {
        ++cnt;
        for (auto c : raw)
        {
            cout << c << ' ';
        }
        cout << endl;
        for (int n = 0; n < i - j; n++)
        {
            cout << ' ' << ' ';
        }
        for (auto c : p)
        {
            cout << c << ' ';
        }
        cout << endl;
        for (int n = 0; n < i; n++)
        {
            cout << ' ' << ' ';
        }
        cout << '^' << endl;
        if (raw[i] == p[j])
        {
            ++i;
            ++j;
            if (j == p.size())
            {
                //finish
                break;
            }
        }
        else
        {
            j = next[j - 1];
        }
    }
    delete[] next;
    return cnt;
}

int main()
{
    string raw, p;
    cin >> raw;
    cin >> p;
    cout << "�Ƚϴ���:" << kmp_and_display(raw, p) << endl;
    system("pause");
    return 0;
}