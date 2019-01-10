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

tree dijkstra(const my_map & m, int start)
{
    //init
    tree spt;
    weight_t min_dst[MAX_V];
    int last_point[MAX_V];
    int V_sqt = 1;                      //the number of vertexs in spt
    int final_point = start;            //the newest one that added into spt
    bool is_selected[MAX_V] = { false, };
    for (int i = 0; i < m.V; i++)
    {
        min_dst[i] = INF;
        last_point[i] = -1;
    }
    min_dst[start] = 0;
    //dijkstra
    while (V_sqt < m.V)
    {
        is_selected[final_point] = true;
        weight_t min = INF;
        for (int i = 0; i < m.V; i++)
        {
            if (!is_selected[i] && m.data[final_point][i] < INF && min_dst[final_point] + m.data[final_point][i] < min_dst[i])
            {
                min_dst[i] = min_dst[final_point] + m.data[final_point][i];
                last_point[i] = final_point;
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
        if (min < INF)
        {
            ++V_sqt;
            spt.push_back({ final_point,last_point[final_point] });
        }
        else
        {
            cout << "error" << endl;
        }
    }
    return spt;
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
    for (int i = 0; i < 6; i++)
    {
        auto spt = dijkstra(m, i);
        cout << "´Ó" << i << "³ö·¢: ";
        for (auto e : spt)
        {
            cout << e.first << '-' << e.second << "   ";
        }
        cout << endl;
    }
    return 0;
}