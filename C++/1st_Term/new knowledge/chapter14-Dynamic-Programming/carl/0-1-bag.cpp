// 0-1背包问题的一维动态规划代码
// 好多问题（例如石头、整数对半分、找符号标注方法……）都可以转化为根本的0-1背包问题
// 即为在数组中任选元素使得和为给定值
// 多重背包，即有多个选择数但并不无限，就展开化为0-1背包来做！
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> list(n);
    int sum = 0;
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
        sum += list[i];
    }
    if (sum % 2 != 0){
        cout << "false" << endl;
        return 0;
    }
    vector<int> dp(sum + 1 , 0);
    for (int i = 0 ; i < n ; i ++){
        for (int j = sum ; j >= 0 && j >= list[i] ; j --){
            dp[j] = max(dp[j] , dp[j - list[i]] + list[i]);
        }
    }
    if (dp[sum / 2] == sum / 2)
        cout << "true" << endl;
    else
        cout << "false" << endl;
    return 0;
}