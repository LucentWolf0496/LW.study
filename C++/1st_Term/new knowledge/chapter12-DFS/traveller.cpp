#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int result = INT_MAX;
void solve(vector<vector<int>> &table , int city , int sum , vector<bool> &visit , int count){  
    if (sum >= result)
        return;
    if (count == visit.size() - 1){
        if (sum + table[city][0] <= result)
            result = sum + table[city][0];
            return;
    }

    for (int i = 1 ; i < visit.size() ; i ++){
        if (!visit[i] && i != city){
            visit[i] = true;
            solve(table , i , sum + table[city][i] , visit , count + 1);
            visit[i] = false;
        }
    }
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> table(n , vector<int>(n));
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            cin >> table[i][j];
        }
    }
    int sum = 0 , count = 0;
    vector<bool> visit(n , false);
    solve(table , 0 , sum , visit , count);
    cout << result << endl;
    return 0;
}