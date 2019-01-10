#ifdef NATIVE
#pragma warning(disable:4996)
#else
#pragma g++ optimize O3
#endif // NATIVE

#include<cstdio>
int N;
struct point
{
    double x, y, f;
};
point buf[4];
point target;
point tmp[2];
int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
    {
        scanf("%lf%lf%lf", &buf[i].x, &buf[i].y, &buf[i].f);
    }
    scanf("%lf%lf", &target.x, &target.y);
    //(x1-x2)(y-y1)=(x-x1)(y1-y2)
    for (int i = 0; i < 2; ++i)
    {
        tmp[i].y = target.y;
        tmp[i].x = (buf[2 * i].x - buf[2 * i + 1].x) * (target.y - buf[2 * i].y) / (buf[2 * i].y - buf[2 * i + 1].y) + buf[2 * i].x;
        tmp[i].f = (buf[2 * i].f - buf[2 * i + 1].f) * (target.y - buf[2 * i].y) / (buf[2 * i].y - buf[2 * i + 1].y) + buf[2 * i].f;
    }
    target.f = (tmp[0].f - tmp[1].f) * (target.x - tmp[0].x) / (tmp[0].x - tmp[1].x) + tmp[0].f;
    printf("%.10lf", target.f);
    return 0;
}