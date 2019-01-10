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
//N皇后
long long solve(int N) {
    vector<Queen>nowQueen;    //用vector模拟栈
    Queen one;
    one.x = 0; one.y = 0;
    long long count = 0;
    do {
        while (one.y < N && find(nowQueen.begin(), nowQueen.end(), one) != nowQueen.end())     //有冲突且y在合理范围，自增y
            ++one.y;
        if (one.y >= N) {    //在当前one.x与前述棋子的情况下，无解，回溯
            one = nowQueen.back();
            nowQueen.pop_back();
            ++one.y;
        }
        else {
            if (one.x == N - 1) {    //一次数完了
                //print
                ++count;
                ++one.y;
            }
            else {    //中间某一层
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