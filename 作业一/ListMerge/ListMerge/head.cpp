//#include<iostream>
/*

struct SNode
{
    int data = 0;
    SNode *next = nullptr;
};

class LinkList
{
public:
    SNode *head = nullptr;
    LinkList()
    {
        head = new SNode;
    }
    LinkList & append(int data)
    {
        SNode *p = head;
        while (p->next != nullptr)
            p = p->next;
        SNode *cur = new SNode{ data,nullptr };
        p->next = cur;
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
    SNode *i = HA.head->next;
    SNode *j = HB.head->next;
    SNode *HC_end = HC.head;
    //make sure HC is empty.
    SNode *cur = HC.head->next;
    while (cur != nullptr)
    {
        SNode *tmp = cur;
        cur = cur->next;
        delete tmp;
        tmp = nullptr;
    }
    HC.head->next = nullptr;
    //merge
    while (i != nullptr || j != nullptr)
    {
        while (i != nullptr && (j == nullptr || i->data <= j->data))
        {
            HC_end->next = i;
            HC_end = i;
            i = i->next;
            HC_end->next = nullptr;
        }
        while (j != nullptr && (i == nullptr || j->data <= i->data))
        {
            HC_end->next = j;
            HC_end = j;
            j = j->next;
            HC_end->next = nullptr;
        }
    }
    HA.head->next = nullptr;
    HB.head->next = nullptr;
}

int main()
{
    LinkList a, b, c;
    a.append(2).append(3).append(3).append(4).append(5).append(7);
    b.append(1).append(4).append(6).append(7);
    mergeList(a, b, c);
    return 0;
}
*/
