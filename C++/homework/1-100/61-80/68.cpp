#include <iostream>
using namespace std;

void f(int x){
    if (x == 1){
        cout << "End" << endl;// 最开始就判断终结，防止输入1后再无效循环一次
        return;
    }
    if (x % 2 == 1){
        cout << x << "*3+1=";
        x = 3 * x + 1;
        cout << x << endl;
    }
    else if (x % 2 == 0){
        cout << x << "/2=";
        x /= 2;
        cout << x << endl;
    }
        f(x);
}

int main(){
    int n = 0;
    cin >> n;
    f(n);
    return 0;
}