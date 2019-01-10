#include<iostream>


struct SNode
{
    int data = 0;
    SNode *next = nullptr;
};

class LinkList
{
public:
    SNode *head = nullptr;
    LinkList & append(int data)
    {
        if (head == nullptr)
            head = new SNode{ data,nullptr };
        else
        {
            SNode *p = head;
            while (p->next != nullptr)
                p = p->next;
            p->next = new SNode{ data,nullptr };
        }
        return *this;
    }
    ~LinkList()
    {
        SNode *cur = head;
        while (cur != nullptr)
        {
            SNode *tmp = cur;
            cur = cur->next;
            delete tmp;
            tmp = nullptr;
        }
        head = nullptr;
    }
};

void mergeList(LinkList &HA, LinkList &HB, LinkList &HC)
{
    SNode *i = HA.head;
    SNode *j = HB.head;
    //make sure HC is empty.
    SNode *cur = HC.head;
    while (cur != nullptr)
    {
        SNode *tmp = cur;
        cur = cur->next;
        delete tmp;
        tmp = nullptr;
    }
    HC.head = nullptr;
    //merge
    SNode *HC_end = nullptr;
    while (i != nullptr || j != nullptr)
    {
        while (i != nullptr && (j == nullptr || i->data <= j->data))
        {
            if (HC.head == nullptr)
            {
                HC.head = i;
                HC_end = HC.head;
            }
            else
            {
                HC_end->next = i;
                HC_end = i;
            }
            i = i->next;
            HC_end->next = nullptr;
        }
        while (j != nullptr && (i == nullptr || j->data <= i->data))
        {
            if (HC_end == nullptr)
            {
                HC.head = j;
                HC_end = HC.head;
            }
            else
            {
                HC_end->next = j;
                HC_end = j;
            }
            j = j->next;
            HC_end->next = nullptr;
        }
    }
    HA.head = nullptr;
    HB.head = nullptr;
}

int main()
{
    LinkList a, b, c;
    mergeList(a, b, c);
    return 0;
}

