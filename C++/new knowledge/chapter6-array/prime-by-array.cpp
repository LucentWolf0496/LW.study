#include <iostream>
#include <cmath> // 用于sqrt函数
using namespace std;

int main() {
    const int n = 100;
    int prime[n + 1] = {0}; // 创建大小为101的数组，索引0-100，初始化为0
                            // 用数组对应编号为0/1标明素数/非素数
    
    // 第一块：初始化prime数组（实际上已经初始化为0）
    for(int c = 2; c <= n; c++) {
        prime[c] = 0; // 0表示素数，1表示合数
    }
    
    // 第二块：初始化正因数d
    int d = 2;
    
    // 第三块：循环筛数
    do {
        // 如果d是素数，标记d的所有倍数
        if(prime[d] == 0) {
            int k = d + d; // 从d的第一个倍数开始
            while(k <= n) {
                prime[k] = 1; // 标记为合数
                k += d; // 移动到下一个倍数
            }
        }
        d++;
    } while(d <= sqrt(n)); // 只需要检查到sqrt(n)
    
    // 输出所有素数
    for(int c = 2; c <= n; c++) {// 从2开始防止单位数1的干扰
        if(prime[c] == 0) {
            cout << c << " ";
        }
    }
    cout << endl;
    
    return 0;
}