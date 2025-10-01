#include <iostream>
#include <string>
using namespace std;

int main(){// 大数幂次运算器，通过字符数组实现，求m的n次方，m和n均为整数
           // 但是m稍大就因为多次进位难以处理，只好使用ds改进的max版本，以作学习
    int m = 0 , n = 0;
    string s1 = "1";// 初始化
    cin >> m >> n;
    for (int i = 1 ; i <= n ; i ++){
        for (int j = 0 ; j < s1.size() ; j ++){
            s1[j] = '0' + (s1[j] - '0') * m;// 注意加个'0'，永远注意单引号的携带！！！
        }
        if (s1[0] > '9')// 首位需要进位就插入0
            s1.insert(0 , "0");// 但是insert命令要加双引号
        for (int j = s1.size() - 1 ; j >= 1 ; j --){// 经典进位器
            while (s1[j] > '9'){
                s1[j] -= 10;
                s1[j - 1] ++;
            }
        }
    }
    cout << s1 << endl;
    return 0;
}