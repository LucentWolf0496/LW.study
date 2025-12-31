#include <iostream>
#include <vector>
using namespace std;
vector<int> dx = {1 , 1 , 1 , 0 , 0 , -1 , -1 , -1};
vector<int> dy = {1 , 0 , -1 , 1 , -1 , 1 , 0 , -1};

int main(){
    int m , n;
    cin >> m >> n;
    vector<vector<int>> table(m , vector<int> (n , 0));
    vector<vector<int>> result(m , vector<int> (n , 0));
    for (int i = 0 ; i < m ; i ++){
        for (int j = 0 ; j < n ; j ++){
            cin >> table[i][j];
        }
    }
    for (int i = 0 ; i < m ; i ++){
        for (int j = 0 ; j < n ; j ++){
            int live = 0;
            for (int k = 0 ; k < 8 ; k ++){
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n){
                    if (table[nx][ny] == 1) live ++;
                }
            }
            if ((table[i][j] == 1 && live >= 2 && live <= 3) || (table[i][j] == 0 && live == 3)) result[i][j] = 1;
        }
    }
    for (int i = 0 ; i < m ; i ++){
        cout << result[i][0];
        for (int j = 1 ; j < n ; j ++){
            cout << " " << result[i][j];
        }
        cout << endl;
    }
}