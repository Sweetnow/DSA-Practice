#include<cstdio>
#include<cstring>
#pragma warning(disable:4996)


const int SZ = 1 << 20;  //����io
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
const int HEADER = -1;    //����ͷ�ڱ�Ԫ��index
const int TRAILER = -2;    //����β�ڱ�Ԫ��index

DATA dataList[MAX];    //������
int lastList[MAX], nextList[MAX];    //����ָ��

int header = TRAILER, trailer = HEADER;    //�ڱ�
int nowSize = 0;    //��¼��ǰ���������һ���λ��-1��ʹ�����еĲ��������չ��С(�������ݸ���)
int listSize = 0;    //��¼����Ĵ�С

//����������Ԫ�أ����ز���λ��arrayIndex
int push_back(const DATA& data) {
    if (listSize == 0) {    //�����һ����㣬������0��λ��
        dataList[nowSize] = data;
        nextList[nowSize] = TRAILER;
        lastList[nowSize] = HEADER;
        trailer = header = nowSize;
        nowSize++;
        listSize++;
        return nowSize - 1;
    }
    else {    //������nowSize��λ��
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

//ʹ�õ�ǰ����Ľ��λ��index��λ��,���ز���λ��arrayIndex
int insert(const DATA& data, int listIndex) {
    if (listSize <= listIndex) {    //������listSize==0��index����listSize�����
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



//��ӡ����
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

//ɾ�� �������� Ϊindex��Ԫ��(�Ͽ�����)���ٶ�index�����������������е�
void remove(int arrayIndex) {
    if (nowSize <= arrayIndex || arrayIndex < 0)
        return;
    if (listSize <= 1) {
        listSize = 0;
        return;
    }
    if (arrayIndex == header) {    //������׽ڵ�
        header = nextList[arrayIndex];
        lastList[nextList[arrayIndex]] = HEADER;
    }
    else if (arrayIndex == trailer) {   //�����ĩ�ڵ�
        trailer = lastList[arrayIndex];
        nextList[lastList[arrayIndex]] = TRAILER;
    }
    else {    //ɶ�����ǣ����м�
        lastList[nextList[arrayIndex]] = lastList[arrayIndex];
        nextList[lastList[arrayIndex]] = nextList[arrayIndex];
    }
    listSize--;
}

//�����һ���������Ӵ���鲢����,������������true
bool game(int arrayIndex) {
    int last = 0, next = 0;    //���봦��һ������
    int current = arrayIndex;
    //�ȼ��next��
    while ((current = nextList[current]) != TRAILER) {
        if (dataList[current] != dataList[arrayIndex])
            break;
        else
            next++;
    }
    current = arrayIndex;
    //���last��
    while ((current = lastList[current]) != HEADER) {
        if (dataList[current] != dataList[arrayIndex])
            break;
        else
            last++;
    }
    if (last + next >= 2) {    //ͬɫ�Ĵ��ڵ���3��
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