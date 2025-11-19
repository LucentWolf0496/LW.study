#include <iostream>
using namespace std;

void f(int &count , int m , int n){// 取引用count使得可以在主函数中用count计数
    if (n * n > m)
        return;
    int temp = n;
    int thu = m;
    if (m % n == 0){
        count ++;
        f(count , m / n , n);
    }
    n = temp + 1;
    m = thu;
    f(count , m , n);// 基于以上保存的数据，进行递归处理
}

int main(){
    int n = 0;
    cin >> n;
    for (int x = 0 ; x < n ; x ++){
        int m = 0;
        cin >> m;
        int count = 1;
        f(count , m , 2);// 包括a=a这种分解
        cout << count << endl;
    }
    return 0;
}