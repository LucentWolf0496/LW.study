#include <iostream>
using namespace std;

void f1(unsigned int x){// 先编码程序设计函数，或者先声明后编码，否则无法调用
    if (x % 2 == 1)
        cout << "win" << endl;
    else if (x % 2 == 0)
        cout << "lose" << endl;
}

int count = 0;
void f(unsigned int x , unsigned int y){// 技巧，涉及乘以二溢出但又必须是整数，用unsigned int扩倍范围
    count ++;
    if (x < y){
        unsigned int temp = x;
        x = y;
        y = temp;
    }
    if (x == y){
        f1(count);
        return;
    }
    else if (x >= 2 * y){
        f1(count);
        return;
    }
    else{
        unsigned int temp = y;
        y = x - y;
        x = temp;
    }
    f(x , y);
}

int main(){
    do{
        unsigned int a , b , temp;
        cin >> a >> b;
        if (a == 0 && b == 0)// 经典退出机制
            return 0;
        if (a < b){
            temp = a;
            a = b;
            b = temp;
        }
        if (a >= 2 * b)
            cout << "win" << endl;
        else
            f(a , b);
        count = 0;
    }while(20230831);
}