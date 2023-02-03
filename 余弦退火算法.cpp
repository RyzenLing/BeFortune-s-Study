#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
const int MAX_ITER = 100000; // 最大迭代次数
const double T_START = 100.0; // 初始温度
const double T_END = 1e-6; // 终止温度
const double T_DELTA = 0.996; // 温度衰减因子
double rand0to1() // 生成0~1的随机数
{
    return (double)rand() / RAND_MAX;
}
double cost(double x) // 模拟计算代价函数的过程
{
    return x * x - 10 * cos(2 * M_PI * x) + 10;
}
double newState(double x) // 生成新状态
{
    return x + (rand0to1() - 0.5) * 2;
}
void SA()
{
    srand(time(NULL));
    double x = rand0to1() * 20 - 10; // 初始状态
    double t = T_START;
    while (t > T_END)
    {
        for (int i = 0; i < MAX_ITER; i++)
        {
            double x_new = newState(x);
            double delta = cost(x_new) - cost(x);
            if (exp(-delta / t) > rand0to1())
            {
                x = x_new;
            }
        }
        t *= T_DELTA;
    }
    cout << "Result: " << x << endl;
}
int main()
{
    SA();
    return 0;
}