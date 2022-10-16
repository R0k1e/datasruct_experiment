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
using namespace std;
void add(const sparmattp *a, const sparmattp *b, sparmattp *c);      //两矩阵相加
void multiple(const sparmattp *a, const sparmattp *b, sparmattp *c); //两矩阵相乘
int judge_add(const sparmattp *a, const sparmattp *b);               //判断能否相加
int judge_multiple(const sparmattp *a, const sparmattp *b);          //判断能否相乘
void input(sparmattp *a);                                            //输入元素到a中
void output(const sparmattp *a);                                     //输出最后矩阵
int main(void)
{
    sparmattp *a = new sparmattp;
    sparmattp *b = new sparmattp;
    sparmattp *c = new sparmattp;
    input(a);
    input(b);
    if (judge_add(a, b))
    {
        cout << "They can't add together" << endl;
    }
    else
    {
        add(a, b, c);
        cout << "Add matrix" << endl;
        output(c);
    }
    if (judge_multiple(a, b))
    {
        cout << "They can't multiple together" << endl;
    }
    else
    {
        multiple(a, b, c);
        cout << "Multiple matrix" << endl;
        output(c);
    }
}

void add(const sparmattp *a, const sparmattp *b, sparmattp *c) //两矩阵相加 
{
    c->data = new element[a->m * a->n];
    int l, m, n;
    l = 0, m = 0, n = 0;
    while (m < a->t && n < b->t)
    {
        if (a->data[m].i == b->data[n].i && a->data[m].j == b->data[n].j) // a,b在同一个位置
        {
            c->data[l].i = a->data[m].i;
            c->data[l].j = a->data[m].j;
            c->data[l].value = a->data[m].value + b->data[n].value; //两个值相加
            l++, m++, n++;
        }
        else if (a->data[m].i * m + a->data[m].j > b->data[n].i * m + b->data[n].j) // a的位置在b的后面
        {
            c->data[l] = b->data[n];
            l++, n++;
        }
        else // a的位置在b前面
        {
            c->data[l] = a->data[m];
            l++, m++;
        }
    }
    while (m < a->t) //将a表中剩余部分接入c
    {
        c->data[l] = a->data[m];
        l++, m++;
    }
    while (n < b->t) //将b表中剩余部分接入c
    {
        c->data[l] = b->data[n];
        l++, n++;
    }
    c->t = l;
    c->m = a->m;
    c->n = a->n;
}
void multiple(const sparmattp *a, const sparmattp *b, sparmattp *c) // 两矩阵相乘 
{
    int l, m, n, i, j;
    l = 0, m = 0, n = 0;
    int d[a->m][b->n] = {0};

    while (m < a->t)
    {
        n = 0;
        while (n < b->t)
        {
            if (a->data[m].j == b->data[n].i)
            {
                d[a->data[m].i - 1][b->data[n].j - 1] += ((a->data[m].value) * (b->data[n].value));
                // 列号= 行号 ，对应位置+=
            }
            n++;
        }
        m++;
    }
    for (i = 0; i < a->m; i++)
    {
        for (j = 0; j < b->n; j++)
        {
            if (d[i][j] != 0)
            {
                c->data[l].i = i + 1;
                c->data[l].j = j + 1;
                c->data[l].value = d[i][j];
                l++; 
            }
        }
    }//将非0元素输入三元组表
    c->t = l;
    c->m = a->m;
    c->n = b->n;
}
void input(sparmattp *a) // 输入元素到a中
{
    int m, n, t;
    int i, j, value;
    int count = 0;
    cout << "Input the row, column and non-zero number of matrix" << endl;

    cin >> m >> n >> t;
    a->m = m;
    a->n = n;
    a->t = t;
    a->data = new element[t];
    do
    {
        cout << "Input the element's row, column and its value" << endl;
        cin >> (a->data)[count].i;
        cin >> a->data[count].j;
        cin >> a->data[count].value;
        count++;
    } while (count < t);
    cout << "Input finished" << endl;
}
int judge_add(const sparmattp *a, const sparmattp *b) //判断能否相加
{
    int flag = 0;
    if (a->m != b->m)
        flag = 1;
    if (a->n != b->n)
        flag = 1;
    return flag;//判断两矩阵行列数是否相同
}
int judge_multiple(const sparmattp *a, const sparmattp *b) //判断能否相乘
{
    int flag = 0;
    if (a->n != b->m)
        flag = 1;
    return flag;//判断第一个矩阵列数是否等于第二个行数
}
void output(const sparmattp *a) //输出最后矩阵 
{
    if (a->t == 0 )
        cout << "NULL" <<endl;
    for (int i = 0; i < a->t; i++)
    {
        cout << "row " << a->data[i].i << endl;
        cout << "column " << a->data[i].j << endl;
        cout << "value " << a->data[i].value << endl;
    }
}
