#include <iostream>
#include <vector>
using namespace std;// 全是细节的左手定则迷宫问题！！！重点复习！！！
                    // 当然，必然不能忘记的细节就是==才是判断！！！
                    // 以及：注意循环内部的索引对不对！！！

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
    if (visit[x][y] > 4){// 细节1：不能只用简单的bool数组判断结束，因为左手定则可能多次走过死胡同的交叉口
                         // 故需要经过某处次数>=5再判断迷宫陷入循环，无法完成
        check = false;
        fin = true;
        return;
    }
    visit[x][y] ++;
    for (int i = -1 ; i <= 2 ; i ++){
        int dirx = (dir + i + 4) % 4;// 细节2：方向判断求余数而不是整除
        int nx = x + dx[dirx];
        int ny = y + dy[dirx];
        if (map[nx][ny] != '#'){// 细节4：如果只是遇到'.'能走，那么终点'T'是不能走的
                                // 故写成只要是墙体'#'就不能走，更稳妥，保证不因为终点掉头
            solve(map , visit , nx , ny , dirx);
            break;
        }
    }

}

int main(){
    int n , m;
    while(cin >> n >> m){
        fin = false;// 细节5：终止标识fin变量对每次输入都要更新
        vector<vector<char>> map(n , vector<char>(m));
        vector<vector<int>> visit(n , vector<int>(m , 0));
        for (int i = 0 ; i < n ; i ++){
            for (int j = 0 ; j < m ; j ++){
                cin >> map[i][j];
            }
        }
        char dir0;
        int dir;
        cin >> dir0;// 细节3：将方向转化成数字，同时对数组顺序加以特化使其可通过循环遍历左上右下的方向
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