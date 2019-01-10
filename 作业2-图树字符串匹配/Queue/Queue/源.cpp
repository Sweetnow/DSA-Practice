#include<iostream>

template <class ElemType,int size>
class CyQueue
{
public:
    int front;//queue[front]是头结点，不存数据
    int rear;
    int MaxSize;
    bool flag;
    ElemType queue[size+1];
    CyQueue()
    {
        flag = 0; front = 0; rear = 0;
        MaxSize = size;
    }
    void EnQueue(ElemType x);
    ElemType OutQueue();
};

template <class ElemType,int size>
void CyQueue<ElemType,size>::EnQueue(ElemType x)
{
    using namespace std;
    if (flag)
    {
        int next_rear = (rear + 1) % (MaxSize + 1);
        if (next_rear == front)
        {
            cout << "Error: Queue is full. Can not push one element." << endl;
        }
        else
        {
            queue[rear = next_rear] = x;
        }
    }
    else
    {
        //queue is empty
        front = 0;
        queue[rear = front + 1] = x;
        flag = true;
    }
}

template <class ElemType,int size>
ElemType CyQueue<ElemType,size>::OutQueue()
{
    using namespace std;
    if (flag)
    {
        front = (front + 1) % (MaxSize + 1);
        flag = (front != rear);
        return queue[front];
    }
    else
    {
        //queue is empty
        cout << "Error: Queue is empty. Can not pop one element.";
        return ElemType();
    }
}
int main()
{
    CyQueue<int,3> a;
    a.EnQueue(1);
    a.EnQueue(2);
    a.EnQueue(3);
    auto p = a.OutQueue();
    p = a.OutQueue();
    return 0;
}