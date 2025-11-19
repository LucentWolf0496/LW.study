#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(){
    vector<vector<int>> dp(17 , vector<int>(1000 , 0));
    for (int i = 0 ; i < 1000 ; i ++){
        dp[0][i] = (i + 1) * (i + 2) / 2;
    }
    for (int i = 1 ; i < 17 ; i ++){
        for (int j = 0 ; j < i + 2 ; j ++){
            dp[i][j] = pow(2 , j + 1) - 1;
        }
    }
    for (int i = 1 ; i < 17 ; i ++){
        for (int j = i + 2 ; ; j ++){
            for (int k = 0 ; k < j ; k ++){
                dp[i][j] += dp[i - 1][k];
            }
            dp[i][j] += j + 1;
            if (dp[i][j] > 400000)
                break;
        }
    }
    int n , m;
    while(cin >> n >> m){
        if (n == 0 && m == 0)
            return 0;
        int count = 0;
        int temp = n;
        while(temp > 0){
            temp /= 2;
            count ++;
        }
        if (m >= count)
            cout << count << endl;
        else if (m == 1)
            cout << n << endl;
        else{
            for (int i = 0 ; ; i ++){
                if (dp[m - 2][i] >= n){
                    cout << i + 1 << endl;
                    break;
                }
            }
        }
    }
}