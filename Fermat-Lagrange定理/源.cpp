/*试探回溯实现任意正整数分解为4个平方数之和*/
#include<iostream>
#include<stack>
#include<cmath>
using namespace std;
struct RESULT {
    int x[4];
};
RESULT solve(int N) {
    stack<int>result;
    int num = sqrt(N);
    do {
        while (num >= 0 && num*num > N)
            --num;
        if (num < 0) {
            num = result.top();
            result.pop();
            N += num * num;
            --num;
        }
        else {
            if (result.size() == 3 && num*num == N) {
                RESULT tmp;
                tmp.x[0] = num;
                for (int i = 1; i < 4; i++) {
                    tmp.x[i] = result.top();
                    result.pop();
                }
                return tmp;
            }
            else {
                result.push(num);
                N -= num * num;
            }
        }
    } while (num >= 0);
    return RESULT();
}
int main() {
    RESULT result = solve(723984);
    for (int i = 0; i < 4; i++) {
        cout << result.x[i] << " ";
    }
    system("pause");
    return 0;
}