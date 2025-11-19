#include <iostream>
#include <vector>
using namespace std;

vector<int> dx = {-1 , 0 , 1 , 0};
vector<int> dy = {0 , 1 , 0 , -1};
bool check = false;
bool fin = false;

void solve(vector<vector<char>> &map , vector<vector<int>> &visit , int x , int y , int dir){
    if (fin)
        return;
    if (map[x][y] == 'T'){
        check = true;
        fin = true;
        return;
    }
    if (visit[x][y] > 1){
        check = false;
        fin = true;
        return;
    }
    visit[x][y] ++;
    for (int i = -1 ; i <= 2 ; i ++){
        int dirx = (dir + i + 4) % 4;
        int nx = x + dx[dirx];
        int ny = y + dy[dirx];
        if (map[nx][ny] != '#'){
            solve(map , visit , nx , ny , dirx);
            break;
        }
    }

}

int main(){
    int n , m;
    while(cin >> n >> m){
        fin = false;
        vector<vector<char>> map(n , vector<char>(m));
        vector<vector<int>> visit(n , vector<int>(m , 0));
        for (int i = 0 ; i < n ; i ++){
            for (int j = 0 ; j < m ; j ++){
                cin >> map[i][j];
            }
        }
        char dir0;
        int dir;
        cin >> dir0;
        if (dir0 == 'N')
            dir = 0;
        if (dir0 == 'E')
            dir = 1;
        if (dir0 == 'S')
           dir = 2;
        if (dir0 == 'W')
            dir = 3;
        int sx , sy;
        for (int i = 0 ; i < n ; i ++){
            for (int j = 0 ; j < m ; j ++){
                if (map[i][j] == 'S'){
                    sx = i;
                    sy = j;
                }
            }
        }
        solve(map , visit , sx , sy , dir);
        if (check)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}