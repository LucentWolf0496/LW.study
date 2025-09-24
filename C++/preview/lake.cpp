#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <climits>
using namespace std;

// 定义方向：上、右、下、左
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

struct Lake {
    int area;
    double total_depth;
    double avg_depth;
};

// 使用BFS算法查找并分析一个湖
Lake analyzeLake(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int i, int j) {
    int n = grid.size();
    int m = grid[0].size();
    
    Lake lake{0, 0.0, 0.0};
    queue<pair<int, int>> q;
    
    q.push({i, j});
    visited[i][j] = true;
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        // 更新湖的统计数据
        lake.area++;
        lake.total_depth += grid[x][y];
        
        // 检查四个方向
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            // 检查是否在边界内且是水域且未访问过
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && 
                grid[nx][ny] > 0 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    
    // 计算平均水深
    lake.avg_depth = lake.total_depth / lake.area;
    
    return lake;
}

int main() {
    int n, m;
    cout << "请输入湖面的行数和列数: ";
    cin >> n >> m;
    
    vector<vector<int>> grid(n, vector<int>(m));
    cout << "请输入湖面区块水深数据 (0表示陆地):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<Lake> lakes;
    
    // 遍历所有区块，寻找未访问的水域
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] > 0 && !visited[i][j]) {
                Lake lake = analyzeLake(grid, visited, i, j);
                lakes.push_back(lake);
            }
        }
    }
    
    // 找出面积最大的湖和平均水深最大的湖
    int max_area = 0;
    double max_avg_depth = 0.0;
    int max_area_index = -1;
    int max_avg_depth_index = -1;
    
    for (int i = 0; i < lakes.size(); i++) {
        if (lakes[i].area > max_area) {
            max_area = lakes[i].area;
            max_area_index = i;
        }
        
        if (lakes[i].avg_depth > max_avg_depth) {
            max_avg_depth = lakes[i].avg_depth;
            max_avg_depth_index = i;
        }
    }
    
    // 输出结果
    cout << "\n分析结果:" << endl;
    cout << "总共发现 " << lakes.size() << " 个湖" << endl;
    
    if (max_area_index != -1) {
        cout << "面积最大的湖: 面积 = " << max_area 
             << ", 平均水深 = " << fixed << setprecision(2) << lakes[max_area_index].avg_depth << endl;
    }
    
    if (max_avg_depth_index != -1) {
        cout << "平均水深最大的湖: 平均水深 = " << fixed << setprecision(2) << max_avg_depth 
             << ", 面积 = " << lakes[max_avg_depth_index].area << endl;
    }
    
    // 输出所有湖的详细信息
    cout << "\n所有湖的详细信息:" << endl;
    for (int i = 0; i < lakes.size(); i++) {
        cout << "湖 " << i+1 << ": 面积 = " << lakes[i].area 
             << ", 总水深 = " << lakes[i].total_depth 
             << ", 平均水深 = " << fixed << setprecision(2) << lakes[i].avg_depth << endl;
    }
    
    return 0;
}