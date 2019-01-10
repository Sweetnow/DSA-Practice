#include<cstdio>
#include<cstring>
#include<cctype>
#include<cstdlib>
#ifndef __OJ__
#pragma warning(disable:4996)
#endif // !__OJ__

const size_t MAX = 100000;

struct toy
{
    enum CTRL_FUNC { SWAP = 0, LOOP = 1, ROTATE = 2 };
    union line
    {
        unsigned char data[4];
        unsigned long x;
    };
    line a, b;
    unsigned count[3];
    unsigned all_count = 0;
    const static unsigned MAX_COUNT[3];
    toy()
    {
        a.x = b.x = 0;
        for (size_t i = 0; i < 3; i++)
        {
            count[i] = 0;
        }
    }
    toy(const toy &right)
    {
        a = right.a;
        b = right.b;
        all_count = right.all_count;
        for (size_t i = 0; i < 3; i++)
        {
            count[i] = right.count[i];
        }
    }
    bool operator==(const toy &right)
    {
        return a.x == right.a.x && b.x == right.b.x;
    }
    bool operator!=(const toy &right)
    {
        return !(*this == right);
    }
    void swap()
    {
        ++all_count;
        count[LOOP] = count[ROTATE] = 0;
        ++count[SWAP];
        unsigned long tmp = a.x;
        a.x = b.x;
        b.x = tmp;
    }
    void loop()
    {
        ++all_count;
        count[SWAP] = count[ROTATE] = 0;
        ++count[LOOP];
        a.x = a.x >> 8 | a.x << 24;
        b.x = b.x >> 8 | b.x << 24;
    }
    void rotate()
    {
        ++all_count;
        count[LOOP] = count[SWAP] = 0;
        ++count[ROTATE];
        char tmp = a.data[1];
        a.data[1] = b.data[1];
        b.data[1] = b.data[2];
        b.data[2] = a.data[2];
        a.data[2] = tmp;
    }
};
const unsigned toy::MAX_COUNT[3] = { 1,4,4 };
decltype(&toy::swap) ctrl_func[3] = { &toy::swap,&toy::loop,&toy::rotate };

template<typename T>
class queue
{
public:
    T top()
    {
        return _container[_front];
    }
    T pop()
    {
        return _container[_front++];
    }
    bool push(T a)
    {
        if (_back < MAX - 1)
        {
            _container[_back++] = a;
            return false;
        }
        else return true;
    }
    bool empty()
    {
        return _front == _back;
    }
    void clear()
    {
        _front = _back = 0;
    }
private:
    T _container[MAX];
    size_t _front = 0, _back = 0;
};

queue<toy> q;

int main()
{
    toy target;
    for (unsigned char i = 0; i < 4; i++)
    {
        target.a.data[i] = i + 1;
        target.b.data[i] = 8 - i;
    }
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        q.clear();
        char buffer[20];
        toy raw;
        toy result;
        bool is_finished = false;
        bool is_out_of_range = false;
        fgets(buffer, 20, stdin);
        int left_num = 0, right_num = 0;
        char *left = buffer, *right = buffer + strlen(buffer);
        while (left_num < 4 && right_num < 4)
        {
            while (!isdigit(*left))++left;
            raw.a.data[left_num++] = *left++ - '0';
            while (!isdigit(*right))--right;
            raw.b.data[right_num++] = *right-- - '0';
        }
        q.push(raw);
        while (!q.empty() && !is_finished && !is_out_of_range)
        {
            toy next = q.pop(), tmp;
            if (next == target) //finish and report
            {
                result = next;
                is_finished = true;
                break;
            }
            for (unsigned i = 0; i < 3; i++)
            {
                if (next.count[i] < toy::MAX_COUNT[i])
                {
                    tmp = next;
                    (tmp.*ctrl_func[i])();
                    if (tmp != raw)
                    {
                        is_out_of_range = q.push(tmp);
                        if (is_out_of_range)
                        {
                            printf("%d\n", -1);
                            break;
                        }
                    }
                }
            }
        }
        printf("%u\n", result.all_count);
    }
#ifndef __OJ__
    getchar();
#endif // !__OJ__
    return 0;
}