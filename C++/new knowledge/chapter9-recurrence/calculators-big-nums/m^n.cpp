#include <iostream>
#include <string>
using namespace std;

int main(){
    int m = 0 , n = 0;
    string s1 = "1";
    cin >> m >> n;
    for (int i = 1 ; i <= n ; i ++){
        int next = 0;
        for (int j = s1.size() - 1 ; j >= 0  ; j --){// 核心问题出在这里，应该从后往前而不是从前往后
                                                     // 细致关注大数运算位数从后往前，用j--来编写
            int digit = (s1[j] - '0') * m + next;
            s1[j] = digit % 10 + '0';
            next = digit / 10;
        }
        while (next > 0){
            s1.insert(0 , "0");// 逻辑是对的，可以一直insret，前面对了就好
                               // insert函数用双引号可以直接选开始位置，但是单引号就需要再来一个长度
            s1[0] = next % 10 + '0';
            next /= 10;
        }
    }
    cout << s1 << endl;
    return 0;
}