#define NATIVE
#include<cstdio>
#include<cmath>
#ifndef NATIVE
#pragma g++ optimize O3
#else
#pragma warning(disable:4996)
#endif // !NATIVE

struct pos
{
    double x, y;
};

inline double get_dst(pos a, pos b)
{
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
inline pos get_perpendicular(pos r, pos a, pos b)
{
    double A = (a.y - b.y);
    double B = -(a.x - b.x);
    double C = (a.x * b.y - b.x * a.y);
    double A_p = B;
    double B_p = -A;
    double C_p = -(A_p*r.x + B_p * r.y);
    return { (B*C_p - B_p * C) / (A*B_p - A_p * B),(A_p*C - A * C_p) / (A*B_p - A_p * B) };
}
int n;
int main()
{
    scanf("%d", &n);
    for (int count = 0; count < n; ++count)
    {
        bool is_empty = true;
        double r;
        pos position[4];
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf",
            &r, &position[0].x, &position[0].y, &position[1].x, &position[1].y, &position[2].x, &position[2].y, &position[3].x, &position[3].y);
        for (int i = 1; i < 4 && is_empty; ++i)
        {
            for (int j = i + 1; j < 4 && is_empty; ++j)
            {
                get_perpendicular(position[0], position[i], position[j]);
                double i_to_circle = get_dst(position[i], position[0]), j_to_circle = get_dst(position[j], position[0]);
                if (i_to_circle == r || j_to_circle == r)       //one on edge
                {
                    //true
                    is_empty = false;
                }
                else if ((i_to_circle > r) ^ (j_to_circle > r)) //one outside one inside 
                {
                    //true
                    is_empty = false;
                }
                else if ((i_to_circle > r) && (j_to_circle > r))
                {
                    auto point = get_perpendicular(position[0], position[i], position[j]);
                    //true
                    if (!((point.x > position[i].x && point.x > position[j].x) || (point.x < position[i].x && point.x < position[j].x))
                        && !((point.y > position[i].y && point.y > position[j].y) || (point.y < position[i].y && point.x < position[j].y))
                        && get_dst(point, position[0]) <= r)
                        is_empty = false;
                }
            }
        }
        printf("%d\n", (is_empty ? 0 : 1));
    }
    return 0;
}