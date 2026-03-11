#include <iostream>
#include <vector>
using namespace std;

vector<int> dx = {1 , 0 , -1 , 0};
vector<int> dy = {0 , 1 , 0 , -1};

void solve(int x , int y , int m , vector<vector<char>> &map , // 改1：对map传引用减少不必要复制步骤
    vector<vector<bool>> &visited , bool &check){
    if (check)// 改2：check了就提前结束函数
        return;
    if (map[x][y] == 'e'){
        check = true;
        return;
    }

    for (int i = 0 ; i < 4 ; i ++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && ny >= 0 && nx < m && ny < m){// 注意：先判断越界再后续判断，好习惯！！
            if (map[nx][ny] != '#' && !visited[nx][ny]){// 改3：只限制墙和访问，不限制终点
                visited[nx][ny] = true;
                solve (nx , ny , m , map , visited , check);
                if (check)// 改2：check了就提前结束函数，注意由于return的层级性质，这里也要加返回
                    return;// 两个返回：可供层层返回直至退回主函数
            }
        }
    }
}

int main(){
    int n = 0;
    cin >> n;
    for (int x = 0 ; x < n ; x ++){
        int m = 0;
        cin >> m;
        vector<vector<bool>> visited(m , vector<bool>(m , false));
        vector<vector<char>> map(m , vector<char>(m));
        for (int i = 0 ; i < m ; i ++){
            for (int j = 0 ; j < m ; j ++){
                cin >> map[i][j];
            }
        }

        bool check = false;
        visited[0][0] = true;
        solve(0 , 0 , m , map , visited , check);
        if (check)
            cout << "YES" << endl;
        if (!check)
            cout << "NO" << endl;
    }
    return 0;
}