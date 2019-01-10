#include<cstdio>
#include<cstdlib>
#pragma warning(disable:4996)
using namespace std;

const int MAX = 1600000;

//bottom->top  0->size
struct Stack {
    int data[MAX];
    int size;
    bool isExistent[MAX + 1];
    Stack() :size(0) {}
    bool empty() {
        return size <= 0;
    }
    void push(int element) {
        data[size++] = element;
        isExistent[element] = true;
    }
    int pop() {
        isExistent[data[--size]] = false;
        return data[size];
    }
    int top() {
        return data[size - 1];
    }
    bool find(int target) {
        return isExistent[target];
    }
}A, B, Mid;

//true为push false为pop
bool PushPop[2 * MAX];
//总操作数
int count = 0;

inline void Push() {
    PushPop[count++] = true;
}
inline void Pop() {
    PushPop[count++] = false;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int tmp;
        A.push(n - i);
        scanf("%d", &tmp);
        B.push(tmp);
    }
    for (int i = 0; i < n; i++) {
        while (!A.empty() && !Mid.find(B.data[i])) {
            Mid.push(A.pop());
            Push();
            if (Mid.size > m) {
                printf("No\n");
                return 0;
            }
        }
        if (Mid.top() == B.data[i]) {
            Mid.pop();
            Pop();
        }
        else {
            printf("No\n");
            return 0;
        }
    }
    for (int i = 0; i < count; i++) {
        if (PushPop[i])
            printf("push\n");
        else
            printf("pop\n");
    }
#ifdef _DEBUG
    system("pause");
#endif // _DEBUG
    return 0;
}