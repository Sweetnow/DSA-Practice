#include <iostream>
#include <vector>
#include <cmath>
#include <array>

using std::array;
using std::cout;
using std::endl;

const int MAX_V = 100;
using weight_t = double;
const weight_t INF = INT_MAX;

using map_mat = array<array<weight_t, MAX_V>, MAX_V>;

struct my_map
{
    int V, E;
    map_mat data;
    my_map(int V) : V(V)
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

map_mat floyd(const my_map &m)
{
    map_mat result = m.data;
    for (int i = 0; i < m.V; i++)
    {
        result[i][i] = 0;
    }
    for (int k = 0; k < m.V; k++)
    {
        for (int i = 0; i < m.V; i++)
        {
            for (int j = 0; j < m.V; j++)
            {
                if (i == j)
                {
                    continue;
                }
                if (result[i][k] < INF && result[k][j] < INF && result[i][k] + result[k][j] < result[i][j])
                {
                    result[i][j] = result[i][k] + result[k][j];
                }
            }
        }
    }
    return result;
}

//only for homework
struct point
{
    int x, y;
};
auto get_dst(const point &a, const point &b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
void add_edge_by_point(my_map &m, point points[], int i, int j)
{
    m.add_edge(i, j, get_dst(points[i], points[j]));
}

int main()
{
    point p[6] = {{1, 3}, {2, 1}, {6, 5}, {3, 4}, {3, 7}, {5, 3}};
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
    auto result = floyd(m);
    return 0;
}