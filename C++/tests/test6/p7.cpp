#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n , m;
vector<vector<char>> table;
vector<vector<int>> island1(2 , vector<int>(2501 , -1));
vector<vector<int>> island2(2 , vector<int>(2501 , -1));
vector<vector<int>> island3(2 , vector<int>(2501 , -1));
vector<vector<bool>> visit;
vector<int> dx = {1 , 0 , -1 , 0};
vector<int> dy = {0 , 1 , 0 , -1};

bool inMap(int x , int y){
    if (x < 0 || x >= n || y < 0 || y >= m) return false;
    return true;
}

void bfs(int x , int y , int count){
    vector<vector<int>> result(2 , vector<int>(2501 , -1));
    queue<pair<int , int>> q;
    q.push({x , y});
    visit[x][y] = true;
    result[0][0] = x;
    result[1][0] = y;
    int num = 1;
    while(!q.empty()){
        int x0 = q.front().first;
        int y0 = q.front().second;
        q.pop();
        for (int i = 0 ; i < 4 ; i ++){
            int nx = x0 + dx[i];
            int ny = y0 + dy[i];
            if (inMap(nx , ny) && table[nx][ny] == 'X' && !visit[nx][ny]){
                q.push({nx , ny});
                visit[nx][ny] = true;
                for (int j = 0 ; j < 4 ; j ++){
                    int px = nx + dx[j];
                    int py = ny + dy[j];
                    if (inMap(px , py) && table[px][py] == '.'){
                        result[0][num] = nx;
                        result[1][num] = ny;
                        num ++;
                        break;
                    }
                }
            }
        }
    }
    if (count == 1) island1 = result;
    if (count == 2) island2 = result;
    if (count == 3) island3 = result;
}

int main(){
    cin >> n >> m;
    vector<vector<char>> xtable(n , vector<char>(m));
    vector<vector<bool>> xvisit(n , vector<bool>(m , false));
    table = xtable;
    visit = xvisit;
    for(int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < m ; j ++){
            cin >> table[i][j];
        }
    }
    int count = 0;
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < m ; j ++){
            if (table[i][j] == 'X' && !visit[i][j]){
                count ++;
                bfs(i , j , count);
            }
        }
    }
    int x = 200;
    int y = 200;
    int z = 200;
    int other = 10000;
    for (int i = 0 ; i < 2502 ; i ++){
        if (island1[0][i] == -1) break;
        for (int j = 0 ; j < 2502 ; j ++){
            if (island2[0][j] == -1) break;
            x = min (x , abs(island1[0][i] - island2[0][j]) + abs(island1[1][i] - island2[1][j]) - 1);
        }
    }
    for (int i = 0 ; i < 2502 ; i ++){
        if (island1[0][i] == -1) break;
        for (int j = 0 ; j < 2502 ; j ++){
            if (island3[0][j] == -1) break;
            y = min (y , abs(island1[0][i] - island3[0][j]) + abs(island1[1][i] - island3[1][j]) - 1);
        }
    }
    for (int i = 0 ; i < 2502 ; i ++){
        if (island2[0][i] == -1) break;
        for (int j = 0 ; j < 2502 ; j ++){
            if (island3[0][j] == -1) break;
            z = min (z , abs(island2[0][i] - island3[0][j]) + abs(island2[1][i] - island3[1][j]) - 1);
        }
    }
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < m ; j ++){
            if (table[i][j] == 'X') continue;
            int temp = 1;
            int tempx = 10000;
            int tempy = 10000;
            int tempz = 10000;
            for (int k = 0 ; k < 2502 ; k ++){
                if (island1[0][k] == -1) break;
                tempx = min(tempx , abs(i - island1[0][k]) + abs(j - island1[1][k]) - 1);
            }
            for (int k = 0 ; k < 2502 ; k ++){
                if (island2[0][k] == -1) break;
                tempy = min(tempy , abs(i - island2[0][k]) + abs(j - island2[1][k]) - 1);
            }
            for (int k = 0 ; k < 2502 ; k ++){
                if (island3[0][k] == -1) break;
                tempz = min(tempz , abs(i - island3[0][k]) + abs(j - island3[1][k]) - 1);
            }
            temp += tempx + tempy + tempz;
            other = min (other , temp);
        }
    }
    cout << min(other , min(x + y , min(x + z , y + z)));
}