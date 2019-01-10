#include<cstdio>
#include<cstdlib>
#include"temperature.h"
const int MAX_STATION = 50000;
const int MAX_HEIGHT = 17;
const int MIN_X = -(1LL << 31);
const int MAX_X = (1LL << 31) - 1;
const int MIN_Y = MIN_X;
const int MAX_Y = MAX_X;

struct station_info
{
    int x;
    int y;
    int temp;
    station_info(int xx = 0, int yy = 0, int ttemp = 0) :x(xx), y(yy), temp(ttemp) {}
};

struct rectangle
{
    int x1, y1, x2, y2;
    bool inside(int x, int y) const   //(x,y) inside this
    {
        return x1 <= x && x <= x2 && y1 <= y && y <= y2;
    }
    bool inside(const rectangle& r) const //r inside this
    {
        return r.x1 >= x1 && r.y1 >= y1 && r.x2 <= x2 && r.y2 <= y2;
    }
    bool overlapped(const rectangle& r) const
    {
        return !(r.x2<x1 || r.x1>x2 || r.y1 > y2 || r.y2 < y1);
    }
};

class kd_tree
{

private:
    enum DIRECTION  { HORIZONTAL, VERTICAL };  //HORIZONTAL -- left right; VERTICAL -- down up
public:
    using index = unsigned;
    using info_ptr = const station_info *;
    void import_infos(const info_ptr pinfos, int num)
    {
        for (int i = 0; i < num; ++i)
        {
            _container[_container_last + i] = pinfos + i;
        }
        _container_last += num;
        sort(0, num, HORIZONTAL);
        create_tree(0, _container_last, 1, HORIZONTAL);
    }
    int query(rectangle r)
    {
        long long sum_of_temp = 0;
        unsigned count = 0;
        search(r, 1, sum_of_temp, count);
        if (count > 0)
            return sum_of_temp / count;
        else
            return 0;
    }
private:
    struct kd_tree_node
    {
        int left, right, down, up;  //[left, right)*[down, up)
        DIRECTION direction;
        index begin, end; //[begin, end) get included info-structs.
        bool is_leaf;
    };
    void search(rectangle r, index root, long long& sum, unsigned& count)
    {
        if (_tree[root].is_leaf)
        {
            info_ptr p = _container[_tree[root].begin];
            if (r.inside(p->x, p->y))
            {
                sum += p->temp;
                ++count;
            }
            return;
        }
        rectangle rct_of_lchild = { _tree[lchild(root)].left, _tree[lchild(root)].down, _tree[lchild(root)].right, _tree[lchild(root)].up };
        rectangle rct_of_rchild = { _tree[rchild(root)].left, _tree[rchild(root)].down, _tree[rchild(root)].right, _tree[rchild(root)].up };
        if (r.inside(rct_of_lchild))
        {
            for (index i = _tree[lchild(root)].begin; i < _tree[lchild(root)].end; i++)
            {
                sum += _container[i]->temp;
                ++count;
            }
        }
        else if (r.overlapped(rct_of_lchild))
        {
            search(r, lchild(root), sum, count);
        }
        if (r.inside(rct_of_rchild))
        {
            for (index i = _tree[rchild(root)].begin; i < _tree[rchild(root)].end; i++)
            {
                sum += _container[i]->temp;
                ++count;
            }
        }
        else if (r.overlapped(rct_of_rchild))
        {
            search(r, rchild(root), sum, count);
        }
    }
    static index lchild(index parent) { return parent * 2; }
    static index rchild(index parent) { return parent * 2 + 1; }
    static index parent(index child) { return child / 2; }
    static index has_parent(index child) { return parent(child) > 0; }
    static int compare(const void *a, const void *b, DIRECTION direction)
    {
        if (direction == HORIZONTAL)
        {
            return (*(const info_ptr*)(a))->x - (*(const info_ptr*)(b))->x;
        }
        else
        {
            return (*(const info_ptr*)(a))->y - (*(const info_ptr*)(b))->y;
        }
    }
    static int compare_horizontal(const void *a, const void *b)
    {
        return compare(a, b, HORIZONTAL);
    }
    static int compare_vertical(const void *a, const void *b)
    {
        return compare(a, b, VERTICAL);
    }

    void sort(index begin, index end, DIRECTION direction)
    {
        qsort(_container + begin, end - begin, sizeof(info_ptr), (direction == HORIZONTAL ? compare_horizontal : compare_vertical));
    }
    index copy_to_back(index src_begin, index src_end)  //return index of result's beginning
    {
        index dst_begin = _container_last;
        for (index i = src_begin; i < src_end; ++i, ++_container_last)
        {
            _container[_container_last] = _container[i];
        }
        return dst_begin;
    }

    void create_tree(index begin, index end, index root, DIRECTION direction)
    {
        _tree[root].begin = begin;
        _tree[root].end = end;
        _tree[root].direction = direction;
        if (direction != HORIZONTAL)    //children is separated by VERTICAL line.
        {
            if (has_parent(root))
            {
                _tree[root].left = _tree[parent(root)].left;
                _tree[root].right = _tree[parent(root)].right;
            }
            else
            {
                _tree[root].down = MIN_X;
                _tree[root].up = MAX_X;
            }
            _tree[root].down = _container[begin]->y;
            _tree[root].up = _container[end - 1]->y;
        }
        else    //children is separated by HORIZONTAL line.
        {
            if (has_parent(root))
            {
                _tree[root].down = _tree[parent(root)].down;
                _tree[root].up = _tree[parent(root)].up;
            }
            else
            {
                _tree[root].down = MIN_Y;
                _tree[root].up = MAX_Y;
            }
            _tree[root].left = _container[begin]->x;
            _tree[root].right = _container[end - 1]->x;
        }

        if (end - begin > 1)
        {
            _tree[root].is_leaf = false;
            index dst_begin = copy_to_back(begin, end);
            index dst_end = dst_begin + end - begin;
            DIRECTION next_direction = (DIRECTION)(1 - direction);
            sort(dst_begin, dst_end, next_direction);
            index mid = (dst_begin + dst_end) / 2;
            create_tree(dst_begin, mid, lchild(root), next_direction);
            create_tree(mid, dst_end, rchild(root), next_direction);
        }
        else
        {
            _tree[root].is_leaf = true;
        }
    }

    kd_tree_node _tree[1 << MAX_HEIGHT];
    info_ptr _container[MAX_HEIGHT * MAX_STATION]; //MAX_STATION * log2(MAX_STATION)
    index _container_last = 0;
};

station_info infos[MAX_STATION];
kd_tree kd;

int main()
{
    int num_of_station = 0;
    rectangle r;
    num_of_station = GetNumOfStation();
    for (int i = 0; i < num_of_station; ++i)
    {
        int x, y, temp;
        GetStationInfo(i, &x, &y, &temp);
        infos[i] = station_info(x, y, temp);
    }
    kd.import_infos(infos, num_of_station);
    while (GetQuery(&r.x1, &r.y1, &r.x2, &r.y2))
    {
        int result = kd.query(r);
#ifndef __OJ__
        printf("%d\n", result);
#endif // !__OJ__
        Response(result);
    }
#ifndef __OJ__
    getchar();
    getchar();
#endif // !__OJ__
    return 0;
}