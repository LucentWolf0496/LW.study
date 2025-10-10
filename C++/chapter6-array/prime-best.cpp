#include <iostream>
using namespace std;

void linearSieve(int n) {
    // 创建标记数组，初始假设所有数都是素数
    bool* isPrime = new bool[n + 1];
    for (int i = 0; i <= n; i++) {
        isPrime[i] = true;
    }
    
    // 创建素数数组，用于存储筛选出的素数
    int* primes = new int[n];
    int primeCount = 0;
    
    // 线性筛法核心逻辑
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes[primeCount++] = i; // 记录素数
        }
        
        // 用当前已得到的素数 primes[j] 去筛掉 i * primes[j]
        for (int j = 0; j < primeCount && i * primes[j] <= n; j++) {
            isPrime[i * primes[j]] = false; // 标记合数
            
            // 关键步骤：保证每个合数只被它的最小质因子筛掉
            if (i % primes[j] == 0) {
                break;// 对i进行break然后遍历i+1，确保每个i只被标记一次
            }
        }
    }
    
    // 输出所有素数
    cout << "素数列表 (2 到 " << n << "):" << endl;
    for (int i = 0; i < primeCount; i++) {
        cout << primes[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl; // 每行输出10个素数
    }
    cout << endl << "共找到 " << primeCount << " 个素数" << endl;
    
    // 释放动态数组内存
    delete[] isPrime;
    delete[] primes;
}

int main() {
    int n;
    cout << "请输入上限 n: ";
    cin >> n;
    
    if (n < 2) {
        cout << "没有素数" << endl;
        return 0;
    }
    
    linearSieve(n);
    return 0;
}