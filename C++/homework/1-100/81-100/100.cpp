#include <iostream>
#include <vector>
using namespace std;

vector<int> dx = {1 , 0 , -1 , 0};
vector<int> dy = {0 , 1 , 0 , -1};

int search(vector<vector<int>> &table , vector<vector<int>> &dp , vector<vector<bool>> &visit , int x , int y){
    if (visit[x][y])
        return dp[x][y];
    visit[x][y] = true;
    int r = table.size();
    int c = table[0].size();
    int result = 1;
    for (int i = 0 ; i < 4 ; i ++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < r && ny >= 0 && ny < c){
            if (table[nx][ny] < table[x][y])
                result = max(search(table , dp , visit , nx , ny) + 1 , result);
        }
    }
    dp[x][y] = result;// 返回result的同时应当更新dp数组
    return result;
}

int main(){
    int r , c;
    cin >> r >> c;
    vector<vector<int>> table(r , vector<int>(c));
    for (int i = 0 ; i < r ; i ++){
        for (int j = 0 ; j < c ; j ++){
            cin >> table[i][j];
        }
    }
    vector<vector<int>> dp(r , vector<int>(c , 1));
    vector<vector<bool>> visit(r , vector<bool>(c , false));
    int result = 0;
    for (int i = 0 ; i < r ; i ++){
        for (int j = 0 ; j < c ; j ++){
            dp[i][j] = search(table , dp , visit , i , j);
            (dp[i][j] > result ? result = dp[i][j] : 33550336);
        }
    }
    cout << result << endl;
}