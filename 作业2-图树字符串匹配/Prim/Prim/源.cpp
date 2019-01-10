#include<iostream>
#include<vector>
#include<cmath>
using std::cout;
using std::endl;
using std::vector;

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

tree prim(const my_map & m)
{
    //assume that m is connected graph.
    //init
    tree mst;
    int V_MST = 0;
    bool is_selected[MAX_V] = { false };    //in MST
    int final_point = 0;
    weight_t min_dst[MAX_V];
    int min_dst_index[MAX_V];   //the distance between i and min_dst_index[i] is equal to min_dst[i]
    for (int i = 0; i < m.V; i++)
    {
        min_dst[i] = INF;
    }
    //prim
    is_selected[final_point] = true;
    ++V_MST;
    while (V_MST < m.V)
    {
        weight_t min = INF;
        for (int i = 0; i < m.V; i++)
        {
            //refresh the min distance between points in MST and one point out of MST
            if (!is_selected[i] && m.get_dst(final_point, i) < min_dst[i])
            {
                min_dst[i] = m.get_dst(final_point, i);
                min_dst_index[i] = final_point;
            }
        }
        for (int i = 0; i < m.V; i++)
        {
            if (!is_selected[i] && min_dst[i] < min)
            {
                min = min_dst[i];
                final_point = i;
            }
        }
        if (min == INF)     //has no next point
        {
            cout << "m is not a connected graph" << endl;
        }
        else
        {
            is_selected[final_point] = true;
            ++V_MST;
            mst.push_back({ final_point,min_dst_index[final_point] });
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
    auto mst = prim(m);
    for (auto e:mst)
    {
        cout << e.first << '-' << e.second << endl;
    }
    return 0;
}