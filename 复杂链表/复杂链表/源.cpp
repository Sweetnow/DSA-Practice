#define NATIVE
#include<cstdio>
#ifdef NATIVE
#pragma warning(disable:4996)
#else
#pragma g++ optimize O3
#endif // NATIVE

struct complex_node
{
    int value;
    complex_node *next;
    complex_node *random;
    complex_node(int value, complex_node *next, complex_node *random) :
        value(value), next(next), random(random)
    {
    }

};

class complex_list
{
public:
    complex_node *head = nullptr;
    complex_node *tail = nullptr;
    ~complex_list()
    {
        while (head != nullptr)
        {
            auto tmp = head;
            head = head->next;
            delete tmp;
        }
        head = tail = nullptr;
    }
    complex_node *append(int value)
    {
        if (head == nullptr)
        {
            tail = head = new complex_node( value,nullptr,nullptr );
        }
        else
        {
            tail->next = new complex_node( value,nullptr,nullptr );
            tail = tail->next;
        }
        return tail;
    }
    complex_node *get(int index)
    {
        if (index < 0)
            return nullptr;
        auto current = head;
        for (int i = 0; i < index && current != nullptr; i++)
        {
            current = current->next;
        }
        return current;
    }
    void del(int index)
    {
        auto prev = get(index - 1);
        auto current = (prev == nullptr ? head : prev->next);
        if (current == nullptr)
            return;
        for (auto tmp = head; tmp != tail; tmp = tmp->next)
        {
            if (tmp->random == current)
                tmp->random = nullptr;
        }
        if (prev == nullptr)
        {
            //current is head
            head = current->next;
            if (head == nullptr)
                tail = nullptr;
            delete current;
        }
        else
        {
            //current is not head and may be trail
            prev->next = current->next;
            if (tail == current)
                tail = prev;
            delete current;
        }
    }
    complex_node *insert(int value, int index, int random)
    {
        //insert node
        auto prev = get(index - 1);
        decltype(prev) current = nullptr;
        if (prev == nullptr)
        {
            //insert as head
            auto tmp = new complex_node{ value,head,nullptr };
            current = tmp;
            head = tmp;
            if (tail == nullptr)
                tail = head;
        }
        else if (prev == tail)
        {
            //insert as trail
            current = append(value);
        }
        else
        {
            current = prev->next = new complex_node( value,prev->next,nullptr );
        }
        //set random
        current->random = get(random);
        return current;
    }
    void display_next(int index)
    {
        for (auto tmp = get(index); tmp != nullptr; tmp = tmp->next)
        {
            printf("%d ", tmp->value);
        }
        printf("%d\n", -1);
    }
    void display_random(int index)
    {
        for (auto tmp = get(index); tmp != nullptr; tmp = tmp->random)
        {
            printf("%d ", tmp->value);
        }
        printf("%d\n", -1);
    }
};


complex_list lst;
int N, M, K, T;


int main()
{
    scanf("%d%d%d%d", &N, &M, &K, &T);
    for (int i = 0; i < N; i++)
    {
        int value;
        scanf("%d", &value);
        lst.append(value);
    }
    for (int i = 0; i < N; i++)
    {
        int index;
        scanf("%d", &index);
        if (index >= 0)
            lst.get(i)->random = lst.get(index);
    }
    for (int i = 0; i < M; i++)
    {
        int index;
        scanf("%d", &index);
        lst.del(index);
    }
    for (int i = 0; i < K; i++)
    {
        int value, index, random_index;
        scanf("%d%d%d", &value, &index, &random_index);
        lst.insert(value, index, random_index);
    }
    lst.display_next(T);
    lst.display_random(T);
#ifdef NATIVE
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();


#endif // NATIVE
    return 0;
}