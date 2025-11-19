#include <iostream>
#include <queue>
#include <vector>
using namespace std;// 有三个注意点借助ds改进了

vector<int> dx{-1 , 0 , 1 , 0};// 常规设置4个方向遍历
vector<int> dy{0 , -1 , 0 , 1};// 由于visited的数组标记，可以完美解决路径重复问题

int Labyrinth(vector<vector<char>> , vector<vector<bool>> , int , int , int , int);// 其实有点小冗杂

int main(){
    int n = 0 , m = 0;
    cin >> n >> m;
    vector<vector<char>> map(n , vector<char> (m));
    vector<vector<bool>> visited(n , vector<bool> (m , false));// 记得给两个数组赋上初态
    
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < m ; j ++){
            cin >> map[i][j];// 有初态才可键入map
        }
    }
    
    int p = 0 , q1 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
            if (map[i][j] == 'S') {// 改1：找起点！！起点不一定在（0 ，0）
                p = i;
                q1 = j;
            }
        }
    }

    int thu = Labyrinth(map , visited , n , m , p , q1);
    cout << thu << endl;
}

int Labyrinth(vector<vector<char>> map , vector<vector<bool>> visited , int n , int m , int p , int q1){
    queue<pair<pair<int, int> , int>> q;// 改2：步骤要塞在坐标结构体内，随“正确判定nx & ny”生效再+1
    q.push({{p , q1} , 0});// 改2：相应地，q类变量也要套两层pair结构体，学习简化的思维！
    visited[p][q1] = true;

    while (!q.empty()) {
        int x = q.front().first.first;// 双层pair结构体表达
        int y = q.front().first.second;
        int count = q.front().second;
        q.pop();

        for (int i = 0 ; i < 4 ; i ++){// 常规4个方向遍历
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < n && ny < m){// 改3：先检查越界，再判断与延拓
                                                        // 这很重要！！越界难以debug出来！！！
                if (map[nx][ny] != '#' && !visited[nx][ny]){
                    visited[nx][ny] = true;
                    q.push({{nx , ny} , count + 1});// 改2：count塞在结构体之中去进行+1
            }
            if (map[nx][ny] == 'T')
                return count + 1;
            }
        }
    }

    return -1;
}