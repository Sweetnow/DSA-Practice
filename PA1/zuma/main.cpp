#include<cstdio>
#include<cstring>
#pragma warning(disable:4996)


const int SZ = 1 << 20;  //快速io
struct fastio {
    char inbuf[SZ];
    char outbuf[SZ];
    fastio() {
        setvbuf(stdin, inbuf, _IOFBF, SZ);
        setvbuf(stdout, outbuf, _IOFBF, SZ);
    }
}io;

typedef char DATA;

const int MAX = 20005;
const int HEADER = -1;    //定义头哨兵元素index
const int TRAILER = -2;    //定义尾哨兵元素index

DATA dataList[MAX];    //数据项
int lastList[MAX], nextList[MAX];    //链表指针

int header = TRAILER, trailer = HEADER;    //哨兵
int nowSize = 0;    //记录当前数组中最后一项的位置-1，使得所有的插入操作扩展大小(避免数据覆盖)
int listSize = 0;    //记录链表的大小

//向链表后添加元素，返回插入位置arrayIndex
int push_back(const DATA& data) {
    if (listSize == 0) {    //插入第一个结点，插入在0的位置
        dataList[nowSize] = data;
        nextList[nowSize] = TRAILER;
        lastList[nowSize] = HEADER;
        trailer = header = nowSize;
        nowSize++;
        listSize++;
        return nowSize - 1;
    }
    else {    //插入在nowSize的位置
        dataList[nowSize] = data;
        nextList[nowSize] = TRAILER;
        lastList[nowSize] = trailer;
        nextList[trailer] = nowSize;
        trailer = nowSize;
        nowSize++;
        listSize++;
        return nowSize - 1;
    }
}

//使得当前插入的结点位于index的位置,返回插入位置arrayIndex
int insert(const DATA& data, int listIndex) {
    if (listSize <= listIndex) {    //涵盖了listSize==0与index超出listSize的情况
        return push_back(data);
    }
    else if (listIndex <= 0) {
        dataList[nowSize] = data;
        nextList[nowSize] = header;
        lastList[nowSize] = HEADER;
        lastList[header] = nowSize;
        header = nowSize;
        nowSize++;
        listSize++;
        return nowSize - 1;
    }
    else {
        int current = header;
        for (int i = 0; i < listIndex; i++)
            current = nextList[current];
        dataList[nowSize] = data;
        nextList[nowSize] = current;
        lastList[nowSize] = lastList[current];
        nextList[lastList[current]] = nowSize;
        lastList[current] = nowSize;
        nowSize++;
        listSize++;
        return nowSize - 1;
    }
}



//打印链表
void print() {
    if (listSize <= 0) {
        printf("-\n");
    }
    else {
        int current = header;
        do {
            putchar(dataList[current]);
            current = nextList[current];
        } while (current != TRAILER);
        putchar('\n');
    }
}

//删除 数组索引 为index的元素(断开链接)，假定index是正常链接在链表中的
void remove(int arrayIndex) {
    if (nowSize <= arrayIndex || arrayIndex < 0)
        return;
    if (listSize <= 1) {
        listSize = 0;
        return;
    }
    if (arrayIndex == header) {    //如果是首节点
        header = nextList[arrayIndex];
        lastList[nextList[arrayIndex]] = HEADER;
    }
    else if (arrayIndex == trailer) {   //如果是末节点
        trailer = lastList[arrayIndex];
        nextList[lastList[arrayIndex]] = TRAILER;
    }
    else {    //啥都不是，在中间
        lastList[nextList[arrayIndex]] = lastList[arrayIndex];
        nextList[lastList[arrayIndex]] = nextList[arrayIndex];
    }
    listSize--;
}

//从最后一次射入珠子处检查并消除,发生消除返回true
bool game(int arrayIndex) {
    int last = 0, next = 0;    //射入处有一个珠子
    int current = arrayIndex;
    //先检查next侧
    while ((current = nextList[current]) != TRAILER) {
        if (dataList[current] != dataList[arrayIndex])
            break;
        else
            next++;
    }
    current = arrayIndex;
    //检查last侧
    while ((current = lastList[current]) != HEADER) {
        if (dataList[current] != dataList[arrayIndex])
            break;
        else
            last++;
    }
    if (last + next >= 2) {    //同色的大于等于3个
        for (int i = 0; i < last; i++)
            remove(lastList[arrayIndex]);
        for (int i = 0; i < next; i++)
            remove(nextList[arrayIndex]);
        if (arrayIndex == header || arrayIndex == trailer)
            remove(arrayIndex);
        else {
            current = lastList[arrayIndex];
            remove(arrayIndex);
            game(current);
        }
        return true;
    }
    else
        return false;
}

int main() {
    char init[MAX / 2], newOne;
    int len, n, index;
    bool finish;
    fgets(init, MAX / 2, stdin);
    len = strlen(init);
    init[len--] = 0;
    for (int i = 0; i < len; i++) {
        push_back(init[i]);
    }
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %c", &index, &newOne);
        game(insert(newOne, index));
        print();
    }
    return 0;
}