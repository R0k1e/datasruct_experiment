#include <iostream>
#include <cstdlib>
//x = n -f(n,y);
//f(n,y) = [f(n-1,y)+y]%n  算出下标
//f(1,y) = 0;

extern bool determine(int x, int y, int n); //判断是否符合条件

bool determine(int n, int x, int y)
{
    int A[n];
    int count, pre, cur;
    cur = 0;
    pre = n - 1;
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
        {
            A[i] = i + 1;
        }
        else
        {
            A[i] = 0;
        }
    } //初始化静态链表
    for (count = 1; count < x; count++)
    {
        cur = A[cur];
        pre = A[pre];
    } //将开始移到x处
    while (A[0] != 0)
    {
        for (count = 1; count < y; count++)
        {
            cur = A[cur];
            pre = A[pre];
        }
        if (cur == 0)
            break;
        A[pre] = A[cur];
        cur = A[cur];
    }
    if (A[0] == 0)
        return true;
    else
        return false;
}