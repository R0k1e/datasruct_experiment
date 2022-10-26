#include <fstream>
#include <iostream>
struct element
{
    int i, j;  // i行j列
    int value; // 存储的值
};
struct sparmattp
{
    int m, n, t;   // 矩阵m行n列,t个非0元素
    element *data; // 实际矩阵所在位置
};
void transport(const sparmattp *a, sparmattp *b) 
{
    int i, j, k;
    b->m = a->n;
    b->n = a->m;
    b->t = a->t;
    b->data = new element[b->t]();
    int num[a->n] = {0};  //每列的非0元素个数
    int cpot[a->n] = {0}; //每列第一个非0元素的位置
    for (i = 0; i < a->t; i++)
        num[a->data[i].j - 1]++; //第j列每有一个就++
    for (i = 1; i < a->n; i++)
        cpot[i] = cpot[i - 1] + num[i - 1];
    for (i = 0; i < b->t; i++)
    {
        j = cpot[a->data[i].j - 1]; //找出a中第i个元素是第几列，并在b中找到其位置
        cpot[a->data[i].j - 1]++;
        b->data[j] = a->data[i];
        k = b->data[j].i;
        b->data[j].i = b->data[j].j;
        b->data[j].j = k;
    }
}