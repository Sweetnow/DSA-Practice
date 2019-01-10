#include<cstdio>
#ifndef __OJ__
#include<cassert>
#pragma warning(disable:4996)
#endif // !__OJ__
const unsigned MAX_TOWN = 10000;
const unsigned MAX_PAIR = 30000;

template<typename T>
class queue
{
public:
    using queue_type = T[MAX_TOWN];
    using queue_index = unsigned;

    void push(const T& in)
    {
        _queue[_trailer++] = in;
    }
    T pop()
    {
        return _queue[_header++];
    }
    bool empty()
    {
        return _header == _trailer;
    }
private:
    queue_type _queue;
    queue_index _header = 0, _trailer = 0;
};

struct vertex
{
    enum broadband { NONE = -1, A = 0, B = 1 };
    broadband used_band = NONE;
};

class edge_list
{
public:
    using edge_list_index = unsigned;
    using vertex_index = unsigned;

    void add_edge(vertex_index a, vertex_index b)
    {
        if (_last[a] == 0)
        {
            _list[a].v = b;
            _last[a] = a;
        }
        else
        {
            _list[_trailer].v = b;
            _list[_last[a]].next = _trailer;
            _last[a] = _trailer++;
        }
        if (_last[b] == 0)
        {
            _list[b].v = a;
            _last[b] = b;
        }
        else
        {
            _list[_trailer].v = a;
            _list[_last[b]].next = _trailer;
            _last[b] = _trailer++;
        }
    }
    vertex_index begin(vertex_index now)
    {
        if (_last[now] == 0)
            return 0;
        else
        {
            _current = now;
            return _list[_current].v;
        }
    }
    vertex_index next()
    {
#ifndef __OJ__
        assert(_current != 0);
#endif // !__OJ__
        _current = _list[_current].next;
        return _list[_current].v;
    }
    constexpr static vertex_index end()
    {
        return 0;
    }
private:
    struct list_node
    {
        vertex_index v;
        edge_list_index next = 0;
    };
    list_node _list[2 * MAX_PAIR + 1];
    edge_list_index _last[MAX_TOWN + 1] = { 0, };
    edge_list_index _trailer = MAX_TOWN + 1;
    edge_list_index _current = 0;
};

unsigned town_num, pair_num;
vertex v[MAX_TOWN + 1];
queue<unsigned> q;
edge_list e;
bool BFS(unsigned start)
{
    q.push(start);
    while (!q.empty())
    {
        start = q.pop();
        for (auto neighbor = e.begin(start); neighbor != e.end(); neighbor = e.next())
        {
            if (v[neighbor].used_band == vertex::NONE)
            {
                v[neighbor].used_band = static_cast<vertex::broadband>(1 - v[start].used_band);
                q.push(neighbor);
            }
            else if (v[neighbor].used_band == v[start].used_band)
                return false;
        }
    }
    return true;
}
int main()
{
    bool is_ok = true;
    scanf("%u%u", &town_num, &pair_num);
    for (unsigned i = 0; i < pair_num; i++)
    {
        unsigned tmp_a, tmp_b;
        scanf("%u%u", &tmp_a, &tmp_b);
        e.add_edge(tmp_a, tmp_b);
    }
    for (unsigned i = 1; i <= town_num; i++)
    {
        if (v[i].used_band == vertex::NONE)
        {
            v[i].used_band = vertex::A;
            if (!(is_ok = BFS(i)))
                break;
        }
    }
    printf("%d", (is_ok ? 1 : -1));
#ifndef __OJ__
    getchar();
    getchar();
#endif // !__OJ__
    return 0;
}