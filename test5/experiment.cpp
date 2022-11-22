#include <iostream>
#include <cstring>
#include <stdio.h>
#include <random>
using namespace std;
int init_arc(int *arc, int V, int E);
void warshall(int *arc, int V);
float average(int *arc, int V);
int main (void)
{
    int V,E;
    cout << "input the number of V and E" << endl; // 输入顶点数和边数
    cin >> V >> E;
    int arc[V][V];
    memset(arc,0,sizeof(arc));
    int *arcpoint = (int*)arc;
    if (init_arc(arcpoint,V,E)) // 随机生成一个邻接矩阵
    {
        cout << "initialize error,too much arc" << endl; // 输入边数过多，无法生成简单有向图
    }
    warshall(arcpoint,V); //用warshall算法求传递闭包
    cout << "The average value is" ;
    printf(" %.4f \n",average(arcpoint,V)); //输出平均值，保留4位小数
    return 0;
}
int init_arc(int *arc ,int V, int E)
{
    int col,raw; // 生成边行列号
    int count = 0; //记录成功生成边数
    random_device rd; // 生成随机数种子
    minstd_rand r_eng(rd()); //随机数生成器
    if (E > V*(V-1))
        return 1;
    while (count<E)
    {
        col = r_eng() % V;
        raw = r_eng() % V; //确定行列号
        if (col == raw) //不包含自环
            continue;
        else if (arc[raw*V+col] ) //不包含平行边 
            continue;
        else
        {
            arc[raw*V+col] = 1;
            count ++;
        }
    }
    return 0;
}
void warshall(int *arc, int V)
{
    int i,j,k;
    for(i = 0; i < V; i++)
    {
        for(j = 0; j < V; j++)
        {
            for(k = 0; k < V ;k++)
            {
                if(arc[j*V+i]&&arc[i*V+k])
                    arc[j*V+k] = 1; //warshall算法
            }
        }
    }
}
float average(int *arc, int V)
{
    int count = 0;
    int i,j;
    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
        {
            if (arc[i*V+j])
                count++;    // 记录矩阵中1的个数
        }
    }
    return (float)count/V; //返回可到达顶点数量的平均值
}