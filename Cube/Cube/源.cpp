#ifdef NATIVE
#pragma warning(disable:4996)
#else
#pragma g++ optimize O3
#endif // NATIVE

#include<cstdio>
#include<queue>
#include<unordered_map>
#include<deque>
using std::deque;
using std::queue;
using std::unordered_map;
using code_t = unsigned long long;
using depth_t = unsigned char;

constexpr code_t pow(int base, int index)
{
    return (index == 0 ? 1 : base * pow(base, index - 1));
}
const code_t POWER6[24] = { pow(6,0),pow(6,1), pow(6,2), pow(6,3),
                                pow(6,4),pow(6,5), pow(6,6), pow(6,7),
                                pow(6,8),pow(6,9), pow(6,10), pow(6,11),
                                pow(6,12),pow(6,13), pow(6,14), pow(6,15),
                                pow(6,16),pow(6,17), pow(6,18), pow(6,19),
                                pow(6,20),pow(6,21), pow(6,22), pow(6,23) };

enum rotation :unsigned char
{
    _FP = 0, _F2 = 1, _FM = 2,
    _RP = 3, _R2 = 4, _RM = 5,
    _UP = 6, _U2 = 7, _UM = 8,
    ROTATION_MAX
};
const char* rotation_str[] = { "F+","F2","F-","R+","R2","R-","U+","U2","U-" };
rotation inverse_rotation(rotation r)
{
    if (r == _FP)r = _FM;
    else if (r == _FM)r = _FP;
    else if (r == _UP)r = _UM;
    else if (r == _UM)r = _UP;
    else if (r == _RP)r = _RM;
    else if (r == _RM)r = _RP;
    return r;
}

inline bool is_rotate_F(rotation r)
{
    return r == _FP || r == _F2 || r == _FM;
}
inline bool is_rotate_R(rotation r)
{
    return r == _RP || r == _R2 || r == _RM;
}
inline bool is_rotate_U(rotation r)
{
    return r == _UP || r == _U2 || r == _UM;
}
const decltype(&is_rotate_F) IS_ROTATE[3] = { &is_rotate_F,&is_rotate_R,&is_rotate_U };
const rotation ARRAY_ROTATION[3][3] = { { _FP,_F2,_FM },
                                        { _RP,_R2,_RM },
                                        { _UP,_U2,_UM } };
enum face :unsigned char
{
    _0F = 0, _0L = 1, _0U = 2,
    _1F = 3, _1U = 4, _1R = 5,
    _2F = 6, _2D = 7, _2L = 8,
    _3F = 9, _3R = 10, _3D = 11,
    _4B = 12, _4U = 13, _4L = 14,
    _5B = 15, _5R = 16, _5U = 17,
    _6B = 18, _6L = 19, _6D = 20,
    _7B = 21, _7D = 22, _7R = 23,
    FACE_MAX = 24
};

enum color :unsigned char
{
    _RED = 0, _ORANGE = 1, _YELLOW = 2,
    _GREEN = 3, _BLUE = 4, _WHITE = 5,
    COLOR_MAX = 6
};

color get_color(face f)
{
    if (f == _0F || f == _1F || f == _2F || f == _3F)
        return _RED;
    if (f == _4B || f == _5B || f == _6B || f == _7B)
        return _ORANGE;
    if (f == _0L || f == _2L || f == _4L || f == _6L)
        return _GREEN;
    if (f == _1R || f == _3R || f == _5R || f == _7R)
        return _BLUE;
    if (f == _0U || f == _1U || f == _4U || f == _5U)
        return _WHITE;
    if (f == _2D || f == _3D || f == _6D || f == _7D)
        return _YELLOW;
    return COLOR_MAX;
}

struct cube
{
    code_t code;
};
template<typename data_t>
struct cube_with_data :public cube
{
    data_t data[FACE_MAX];
};
using cube_raw = cube_with_data<face>;
using cube_color = cube_with_data<color>;

cube encode(cube_color & cc)
{
    cc.code = 0;
    for (int i = 0; i < static_cast<int>(FACE_MAX); ++i)
    {
        cc.code += static_cast<code_t>(cc.data[i]) * POWER6[i];
    }
    return cc;
}
cube encode(cube_raw & cr)
{
    cr.code = 0;
    for (int i = 0; i < static_cast<int>(FACE_MAX); ++i)
    {
        cr.code += static_cast<code_t>(get_color(cr.data[i])) * POWER6[i];
    }
    return cr;
}
cube_color decode(cube & c)
{
    cube_color cc;
    cc.code = c.code;
    code_t tmp = cc.code;
    for (int i = static_cast<int>(FACE_MAX) - 1; i >= 0; --i)
    {
        cc.data[i] = static_cast<color>(tmp / POWER6[i]);
        tmp %= POWER6[i];
    }
    return cc;
}

//r==*P,             r==*M,           r==*2  
//  t1 t2 --\ t4 t1  t1 t2 --\ t2 t3    t1 t2 --\ t3 t4
//  t4 t3 --/ t3 t2  t4 t3 --/ t1 t4    t4 t3 --/ t2 t1
//T must be basic type.(FOR SPEED)
template<typename T>
void swap4(T& t1, T& t2, T& t3, T& t4, rotation r)
{
    T tmp[4];
    switch (r)
    {
    case _FP:case _RP:case _UP:
        tmp[0] = t4; tmp[1] = t1; tmp[2] = t3; tmp[3] = t2;
        break;
    case _FM:case _RM:case _UM:
        tmp[0] = t2; tmp[1] = t3; tmp[2] = t1; tmp[3] = t4;
        break;
    case _F2:case _R2:case _U2:
        tmp[0] = t3; tmp[1] = t4; tmp[2] = t2; tmp[3] = t1;
        break;
    }
    t1 = tmp[0]; t2 = tmp[1]; t4 = tmp[2]; t3 = tmp[3];
    return;
}

template<typename data_t>
cube rotate(cube_with_data<data_t> &c, rotation r)
{
    switch (r)
    {
    case _FP:case _F2:case _FM:
        swap4(c.data[_0F], c.data[_1F], c.data[_3F], c.data[_2F], r);
        swap4(c.data[_0U], c.data[_1R], c.data[_3D], c.data[_2L], r);
        swap4(c.data[_0L], c.data[_1U], c.data[_3R], c.data[_2D], r);
        break;
    case _RP:case _R2:case _RM:
        swap4(c.data[_1R], c.data[_5R], c.data[_7R], c.data[_3R], r);
        swap4(c.data[_1U], c.data[_5B], c.data[_7D], c.data[_3F], r);
        swap4(c.data[_1F], c.data[_5U], c.data[_7B], c.data[_3D], r);
        break;
    case _UP:case _U2:case _UM:
        swap4(c.data[_0U], c.data[_4U], c.data[_5U], c.data[_1U], r);
        swap4(c.data[_0F], c.data[_4L], c.data[_5B], c.data[_1R], r);
        swap4(c.data[_0L], c.data[_4B], c.data[_5R], c.data[_1F], r);
        break;
    }
    return encode(c);
}

cube rotate(cube &c, rotation r)
{
    cube_color tmp = decode(c);
    return rotate(tmp, r);
}

struct cube_pair
{
    cube c;
    rotation last;
    cube_pair(cube c, rotation last) :c(c), last(last)
    {
    }
    cube_pair() :last(ROTATION_MAX)
    {
    }
    cube_pair add_rotation(rotation r)
    {
        cube tmp = c;
        return { rotate(tmp,r),r };
    }
};
struct cube_pair_with_depth :public cube_pair
{
    depth_t depth;
    cube_pair_with_depth() :cube_pair(), depth(0)
    {
    }
    cube_pair_with_depth(const cube_pair &cp, depth_t depth) :cube_pair(cp), depth(depth)
    {
    }
    cube_pair_with_depth(cube c, rotation r, depth_t depth) :cube_pair(c, r), depth(depth)
    {
    }
};

cube_raw start, target;
//front==1, back==0
queue<cube_pair_with_depth> q[2];
unordered_map<code_t, cube_pair> umap[2];

//if cu in umap[do_front], return 0
//if cu in umap[!do_front], return 1
//else return -1, just continue
int check(code_t cu, bool do_front)
{
    if (umap[do_front].find(cu) == umap[do_front].end())
    {
        if (umap[!do_front].find(cu) == umap[!do_front].end())
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

void finish(code_t code)
{
    deque<rotation> result;
    //code->start
    code_t front_code = code;
    while (front_code != start.code)
    {
        result.push_back(umap[1][front_code].last);
        front_code = umap[1][front_code].c.code;
    }
    code_t back_code = code;
    while (back_code != target.code)
    {
        result.push_front(inverse_rotation(umap[0][back_code].last));
        back_code = umap[0][back_code].c.code;
    }
    printf("%d\n", result.size());
    while (!result.empty())
    {
        rotation r = result.back();
        result.pop_back();
        printf("%s\n", rotation_str[r]);
        rotate(start, r);
        printf("%d", static_cast<int>(start.data[0]));
        for (int i = 1; i < static_cast<int>(FACE_MAX); ++i)
        {
            printf(" %d", static_cast<int>(start.data[i]));
        }
        putchar('\n');
    }
    return;
}

//return 1 when finishing
bool bfs(depth_t now_depth[], bool& do_front)
{
    cube_pair tmp;
    cube_pair_with_depth cu;
    cu = q[do_front].front();
    if (cu.depth > now_depth[do_front])
    {
        now_depth[do_front] = cu.depth;
        do_front = !do_front;
        return false;
    }
    q[do_front].pop();
    for (int i = 0; i < 3; ++i)
    {
        if (!(*IS_ROTATE[i])(cu.last))
        {
            for (rotation r : ARRAY_ROTATION[i])
            {
                tmp = cu.add_rotation(r);
                switch (check(tmp.c.code, do_front))
                {
                case 1:
                    umap[do_front][tmp.c.code] = { cu.c,r };    //cube_pair contains last cube and rotation(to now) here. It is different from others.
                    finish(tmp.c.code);
                    return true;
                    break;
                case -1:
                    q[do_front].emplace(tmp, cu.depth + 1);
                    umap[do_front][tmp.c.code] = { cu.c,r };
                default:
                    break;
                }
            }
        }
    }
    return false;
}

int main()
{
    depth_t now_depth[2] = { 0,0 };
    bool do_front = true;
    //init & input
    for (int i = 0; i < static_cast<int>(FACE_MAX); ++i)
    {
        int tmp;
        scanf("%d", &tmp);
        start.data[i] = static_cast<face>(tmp);
        target.data[i] = static_cast<face>(i);
    }
    //bfs
    q[1].emplace(encode(start), ROTATION_MAX, 0);
    umap[1][start.code] = {};
    q[0].emplace(encode(target), ROTATION_MAX, 0);
    umap[0][target.code] = {};
    if (start.code == target.code)
    {
        finish(start.code);
        return 0;
    }
    while (!bfs(now_depth, do_front))
    {
    }
    return 0;
}