#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

static bool compare(vector<int> &x , vector<int> &y){
    return x[0] < y[0];
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> table(n , vector<int>(2));
    for (int i = 0 ; i < n ; i ++){
        cin >> table[i][0] >> table[i][1];
    }
    sort(table.begin() , table.end() , compare);
    int result = 1;
    vector<int> dp(n , 1);
    for (int i = 0 ; i < n ; i ++){
        for (int j = i - 1 ; j >= 0 ; j --){
            if (table[i][0] > table[j][0] && table[i][1] > table[j][1]) dp[i] = max(dp[i] , dp[j] + 1);
        }
        result = max(result , dp[i]);
    }
    cout << result;
}