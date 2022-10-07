#include<iostream>
#include<string>
#include<cstdlib>
#include<stack>
int main ()
{
    using namespace std;
    stack <string> num,ch; //使用string类型的栈完成操作，其中一个为数字栈，另一个为字符栈
    string in;
    string a;
    string b;
    string c;
    string d;
    cin >> in;
    int i=0,j=1,judge=1; //judge为判断输入合法与否的变量
    for(i=0;i<=in.length()-1;i++)
    {
        if(in[i]>='0'&&in[i]<='9') //若此字符为数字
        {
            a+=in[i];
            while(in[i+1]>='0'&&in[i+1]<='9')//若之后若干位字符仍为数字，则所有数字位共同组成一个数
            {
                a+=in[i+1];
                i++;
            }
            if(in[i]<'0'||in[i]>'9')
                i--;
            num.push(a);
            a.clear(); //清空字符串a
        }
        else if(in[i]=='+'||in[i]=='-'||in[i]=='*'||in[i]=='/') //若此字符为加减乘除运算符
        {
            if(!num.empty()) //若数字栈不为空，则将运算符存入字符栈中，否则视为非法输入
            {
                c+=in[i];
                ch.push(c);
                c.clear();
            }
            else
            {
                cout << "invalid input";
                judge=0;
                break;
            }
        }
        else if(in[i]==')') //若此字符为右括号，则形成一个表达式
        {
            if(!num.empty()&&!ch.empty())
            {
                b+=')';
                b=num.top()+b;
                num.pop();
                b=ch.top()+b;
                ch.pop();
                if(!num.empty())
                {
                    b=num.top()+b;
                    num.pop();
                    b='('+b;
                    num.push(b);
                    b.clear();
                }
                else
                {
                    cout << "invalid input";
                    judge=0;
                    break;
                }
            }
            else
            {
                cout << "invalid input";
                judge=0;
                break;
            }
        }
        else //若此字符不再上列之中，则为非法输入
        {
            cout << "invalid input";
            judge=0;
            break;
        }
    }
    if(judge==1)
    {
        d=num.top()+d;
        num.pop();
        if(num.empty()&&ch.empty()) //若数字栈与字符栈均为空，则输入合法，否则输入非法
            cout << d;
        else
            cout << "invalid input";
    }
    system("pause");
    return 0;
}
