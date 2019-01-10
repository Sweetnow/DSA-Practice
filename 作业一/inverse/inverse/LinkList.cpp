#include<iostream>

struct SNode
{
    int data = 0;
    SNode *next = NULL;
};
struct LinkList
{
    SNode *head = nullptr;
    LinkList & append(int x)
    {
        if (head == nullptr)
        {
            head = new SNode{ x,nullptr };
        }
        else
        {
            SNode *end = head;
            while (end->next != nullptr)
                end = end->next;
            end->next = new SNode{ x,nullptr };
        }
        return *this;
    }
    ~LinkList()
    {
        SNode *cur = head;
        SNode *tmp = nullptr;
        while (cur != nullptr)
        {
            tmp = cur;
            cur = cur->next;
            delete tmp;
            tmp = nullptr;
        }
        head = nullptr;
    }
};

void inverseLinkList(LinkList &HL)
{
    if (HL.head == nullptr || HL.head->next == nullptr) //zero or one node
        return;
    SNode *before = HL.head;
    SNode *cur = before->next;
    SNode *after = cur->next;
    while (after != nullptr)
    {
        cur->next = before;
        before = cur;
        cur = after;
        after = after->next;
    }
    //after==nullptr
    cur->next = before;
    HL.head->next = nullptr;
    HL.head = cur;
}
int main()
{
    LinkList a;
    a.append(1).append(3).append(5).append(7).append(8);
    inverseLinkList(a);
    return 0;
}