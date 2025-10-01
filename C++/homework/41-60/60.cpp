#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int f1(int x , int y){// 转化输出y进制下的x
    int sum = 0 , count = 0;
    while(x > 0){
        sum += pow(y , count) * (x % 10);
        count ++;
        x /= 10;
    }
    return sum;
}

int f2(int x){// 找出数的最大数字
    int temp = 0;
    while(x > 0){
        if (x % 10 > temp)
            temp = x % 10;
        x /= 10;
    }
    return temp;
}

int f3(int x , int y , int z){// 三个数处理最大数字
    if (f2(x) >= f2(y) && f2(x) >= f2(z))
        return f2(x);
    else if (f2(y) >= f2(x) && f2(y) >= f2(z))
        return f2(y);
    else if (f2(z) >= f2(x) && f2(z) >= f2(y))
        return f2(z);
}

int main(){
    int n = 0;
    cin >> n;
    for (int i = 1 ; i <= n ; i ++){
        int a = 0 , b = 0 , c = 0 , check = 0;
        cin >> a >> b >> c;
        int k = f3(a , b , c);
        for (int j = k + 1 ; j <= 1000 ; j ++){
            if (f1(a , j) * f1(b , j) == f1(c , j)){
                cout << j << endl;
                check ++;
                break;
            }
        }
        if (check == 0)
            cout << 0 << endl;
    }
}