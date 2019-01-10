#include<iostream>
#include<vector>
#include<cmath>
#include<map>
using std::cout;
using std::endl;
using std::vector;
using std::multimap;

using weight_t = double;
using edge = std::pair<int, int>;
using tree = vector<edge>;

const int MAX_V = 100;
const weight_t INF = INT_MAX;

struct my_map
{
    int V, E;
    weight_t data[MAX_V][MAX_V];
    my_map(int V) :V(V)
    {
        E = 0;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                data[i][j] = INF;
            }
        }
    }
    void add_edge(int i, int j, weight_t w)
    {
        ++E;
        data[i][j] = data[j][i] = w;
    }
    weight_t get_dst(int i, int j) const
    {
        return data[i][j];
    }
};

struct union_find_set
{
    int V;
    int parent[MAX_V];
    union_find_set(int V) :V(V)
    {
        for (int i = 0; i < V; i++)
        {
            parent[i] = i;
        }
    }
    int find(int i)
    {
        int p = parent[i];
        while (p != parent[p])
            p = parent[p];
        parent[i] = p;
        return p;
    }
    void unite(int i, int j)
    {
        parent[find(j)] = find(i);
    }
    bool is_same(int i, int j)
    {
        return find(i) == find(j);
    }
};

tree kruskal(const my_map & m)
{
    tree mst;
    union_find_set u(m.V);
    //using std::map for sorting (just easy)
    multimap<weight_t, edge> tmp;
    for (int i = 0; i < m.V; i++)
    {
        for (int j = i + 1; j < m.V; j++)
        {
            if (m.get_dst(i, j) < INF)
                tmp.insert({ m.get_dst(i, j), edge{ i,j } });
        }
    }
    for (auto & one : tmp)
    {
        if (u.is_same(one.second.first, one.second.second))
        {
            continue;
        }
        else
        {
            mst.push_back(one.second);
            u.unite(one.second.first, one.second.second);
        }
    }
    return mst;
}

//only for homework
struct point
{
    int x, y;
};
auto get_dst(const point &a, const point &b)
{
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
void add_edge_by_point(my_map & m, point points[], int i, int j)
{
    m.add_edge(i, j, get_dst(points[i], points[j]));
}

int main()
{
    point p[6] = { {1,3},{2,1},{6,5},{3,4},{3,7},{5,3} };
    my_map m(6);
    add_edge_by_point(m, p, 1, 0);
    add_edge_by_point(m, p, 3, 5);
    add_edge_by_point(m, p, 5, 2);
    add_edge_by_point(m, p, 3, 4);
    add_edge_by_point(m, p, 5, 1);
    add_edge_by_point(m, p, 0, 3);
    add_edge_by_point(m, p, 0, 4);
    add_edge_by_point(m, p, 4, 2);
    add_edge_by_point(m, p, 2, 3);
    auto mst = kruskal(m);
    for (auto e : mst)
    {
        cout << e.first << '-' << e.second << endl;
    }
    return 0;
}