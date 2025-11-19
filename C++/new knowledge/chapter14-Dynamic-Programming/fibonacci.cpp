#include <iostream>
#include <vector>
using namespace std;

int fibonacci(int n) {// 初识“动态规划”
    if (n <= 1) return n;
    vector<int> dp(n+1);// 数组动态存储序列数，保证相加不用再算一遍全程递归
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];// 如上，用数组暂存这些算过的数据，直接调用即可
    }
    return dp[n];
}

int main() {
    int n = 0;
    cout << "type the ranking :";
    cin >> n;
    cout << "Fibonacci(" << n << ") = " << fibonacci(n) << std::endl;
    return 0;
}