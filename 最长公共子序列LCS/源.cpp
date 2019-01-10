#include<iostream>
#include<string>
using namespace std;
//string长度为len [0-len-1],递归算法 O(2^n)
int LCS(const char* string1, const char* string2, int len1, int len2) {
    //recursive basis
    if (len1 == 0 || len2 == 0)
        return 0;
    else if (len1 == 1 && len2 == 1)
        return string1[0] == string2[0];
    //recursion
    else {
        if (string1[len1 - 1] == string2[len2 - 1])
            return 1 + LCS(string1, string2, len1 - 1, len2 - 1);
        else {
            int tmp1, tmp2;
            tmp1 = LCS(string1, string2, len1 - 1, len2);
            tmp2 = LCS(string1, string2, len1, len2 - 1);
            return tmp1 > tmp2 ? tmp1 : tmp2;
        }
    }
}

//动态规划 O(m*n)?
int LCS_Omn(const char* string1, const char* string2, int len1, int len2) {
    int** result = new int*[len1];
    int finally;
    for (int i = 0; i < len1; i++)
        result[i] = new int[len2];
    //start
    result[0][0] = string1[0] == string2[0];
    for (int i = 1; i < len1; i++)
        result[i][0] = result[i - 1][0] || string1[i] == string2[0];
    for (int j = 1; j < len2; j++)
        result[0][j] = result[0][j - 1] || string1[0] == string2[j];
    for (int i = 1; i < len1; i++)
        for (int j = 1; j < len2; j++)
            if (string1[i] == string2[j])
                result[i][j] = 1 + result[i - 1][j - 1];
            else
                result[i][j] = (result[i][j - 1] > result[i - 1][j] ? result[i][j - 1] : result[i - 1][j]);
    finally = result[len1 - 1][len2 - 1];
    //stop
    for (int i = len1 - 1; i >= 0; i--)
        delete[]result[i];
    delete[]result;
    return finally;
}

int main() {
    string a, b;
    do {
        cin >> a >> b;
        cout <<LCS_Omn(a.data(), b.data(), a.length(), b.length()) << "\n";
    } while (a != "0" || b != "0");
    system("pause");
    return 0;
}