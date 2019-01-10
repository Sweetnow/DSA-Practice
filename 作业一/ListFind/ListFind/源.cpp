#include<iostream>

using ElemType = int;
struct NODE
{
    ElemType data = 0;
    NODE *next = NULL;
};

NODE *list_find(NODE *current, ElemType x)
{
    if (current == NULL)
        return NULL;
    if (current->data == x)
    {
        return current;
    }
    else
    {
        return list_find(current->next, x);
    }
}

int main()
{
    NODE *head = NULL;
    auto a = list_find(head, 100);

    return 0;
}
