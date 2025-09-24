// 复杂度为O(n),使用vector确保对每个合数只标记一次,从而只是线性操作，简化程序运算量！
// vector动态数组机制好！
#include <iostream>
#include <vector>
using namespace std;

vector<int> linearSieve(int n) {
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
        for (int p : primes) {
            if (i * p > n) break;
            isPrime[i * p] = false;
            if (i % p == 0) break; // 关键：确保每个合数只被最小质因子标记
        }
    }
    return primes;
}

int main() {
    int n = 100;
    vector<int> primes = linearSieve(n);
    cout << "Primes up to " << n << ": ";
    for (int p : primes) {
        cout << p << " ";
    }
    cout << endl;
    return 0;
}