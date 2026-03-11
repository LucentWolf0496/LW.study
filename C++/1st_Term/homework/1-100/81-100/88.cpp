#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> dx = {1 , 0 , -1 , 0};
vector<int> dy = {0 , 1 , 0 , -1};

int main(){
    int x , y;
    while(cin >> x >> y){
        if (x == 0 && y == 0)
            return 0;
        vector<vector<char>> table(y , vector<char>(x));// 细节1：给出的迷宫是char，应该用char作为变量
        vector<vector<bool>> check(y , vector<bool>(x , false));
        for (int i = 0 ; i < y ; i ++){
            for (int j = 0 ; j < x ; j ++){
                cin >> table[i][j];
            }
        }
        int sx = 0 , sy = 0;
        for (int i = 0 ; i < y ; i ++){
            for (int j = 0 ; j < x ; j ++){
                if (table[i][j] == '@'){
                    sx = i;
                    sy = j;
                    break;
                }
            }
        }

        queue<pair<int , int>> q;
        q.push({sx , sy});
        check[sx][sy] = true;
        int count = 1;// 细节2：初态要记录check数组并且记录一个count
        while (!q.empty()){
            int xp = q.front().first;
            int yp = q.front().second;
            q.pop();

            for (int i = 0 ; i < 4 ; i ++){
                int nx = xp + dx[i];
                int ny = yp + dy[i];
                if (nx >= 0 && nx < y && ny >= 0 && ny < x){
                    if (table[nx][ny] == '.' && !check[nx][ny]){
                        check[nx][ny] = true;
                        q.push({nx , ny});
                        count ++;
                    }
                }
            }
        }

        cout << count << endl;
    }
}