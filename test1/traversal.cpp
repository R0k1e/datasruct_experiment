#include <iostream>
#include <cstdlib>
#include "determine.cpp"
using namespace std;
const int Y = 20; // count number
const int N = 10; // total number
extern bool determine(int n,int x,int y);
int main(void)
{
    int n, y, x;
    for (n = 2; n <= N; n++)
    {
        for (x = 1; x <= n; x++)
        {
            for (y = 1; y <= Y; y++)
            {
                if (determine(n, x, y))
                {
                    cout << "n=" << n << "     x=" << x << "     y=" << y << endl;
                }
            }
        }
    }
}
