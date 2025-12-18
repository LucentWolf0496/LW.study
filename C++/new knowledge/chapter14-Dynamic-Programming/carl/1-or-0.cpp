// 二维背包，有0数目和1数目两个限定要求
// 注意此时可以允许0/1任一维度质量是0而另一维度可以容纳
// 注意要从后往前遍历背包，确保状态方程转移的正确性
// 确保每个dp轮次都是基于上一个轮次的动态变化，而非混杂的dp层次
// 本题其实相当于把三维dp简化成了二维
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<string> list(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    int x0 , x1;
    cin >> x0 >> x1;
    vector<vector<int>> dp(x0 + 1 , vector<int>(x1 + 1 , 0));// 此题必须数组大小+1，因为背包可以允许一个质量维度为0
    for (int i = 0 ; i < n ; i ++){
        int zero = 0;
        int one = 0;
        for (int j = 0 ; j < list[i].size() ; j ++){
            if (list[i][j] == '0')
                zero ++;
        }
        one = list[i].size() - zero;
        for (int j = x0 ; j >= zero ; j --){// 数组大小+1，从x0和x1开始递减
            for (int k = x1 ; k >= one ; k --){
                dp[j][k] = max(dp[j][k] , dp[j - zero][k - one] + 1);
            }
        }
    }
    cout << dp[x0][x1] << endl;
}