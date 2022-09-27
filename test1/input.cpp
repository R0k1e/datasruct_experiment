#include <iostream>
#include <cstdlib>
#include "determine.cpp"
using namespace std;
extern bool determine(int n,int x,int y);
int main (void)
{
    int n,x,y;
    cout << "input n,x,y" << endl;
    cin >>n >>x >>y;
    if (determine(n,x,y)) 
    {
        cout << "Yes";
    }
    else 
    {
        cout << "No";
    }
}
