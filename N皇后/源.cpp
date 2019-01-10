#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Queen {
    int x, y;
    bool operator==(const Queen& another) {
        return x == another.x || y == another.y || x + y == another.x + another.y || x - y == another.x - another.y;
    }
    bool operator!=(const Queen& another) {
        return !(*this == another);
    }
};
//N�ʺ�
long long solve(int N) {
    vector<Queen>nowQueen;    //��vectorģ��ջ
    Queen one;
    one.x = 0; one.y = 0;
    long long count = 0;
    do {
        while (one.y < N && find(nowQueen.begin(), nowQueen.end(), one) != nowQueen.end())     //�г�ͻ��y�ں���Χ������y
            ++one.y;
        if (one.y >= N) {    //�ڵ�ǰone.x��ǰ�����ӵ�����£��޽⣬����
            one = nowQueen.back();
            nowQueen.pop_back();
            ++one.y;
        }
        else {
            if (one.x == N - 1) {    //һ��������
                //print
                ++count;
                ++one.y;
            }
            else {    //�м�ĳһ��
                nowQueen.push_back(one);
                ++one.x;
                one.y = 0;
            }
        }
    } while (!(one.x == 0 && one.y >= N));
    return count;
}


int main() {
    for (int i = 1; i <= 25; i++) {
        cout << solve(i) << endl;
    }
    system("pause");
    return 0;
}