#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>
#include <queue>

using namespace std;

// 生成符合自然规律的湖
vector<vector<int>> generateNaturalLake(int rows, int cols) {
    vector<vector<int>> lake(rows, vector<int>(cols, 0));
    
    // 随机数生成器
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> centerRow(rows/4, 3*rows/4);
    uniform_int_distribution<> centerCol(cols/4, 3*cols/4);
    uniform_real_distribution<> dis(0.0, 1.0);
    
    // 随机选择几个中心点（湖的最深处）
    int numCenters = 3 + gen() % 3; // 3-5个中心点
    vector<pair<int, int>> centers;
    vector<int> centerDepths;
    
    for (int i = 0; i < numCenters; i++) {
        centers.push_back({centerRow(gen), centerCol(gen)});
        centerDepths.push_back(8 + gen() % 5); // 中心深度8-12
    }
    
    // 使用BFS从中心点向外扩散，生成湖的形状
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<pair<int, int>> q;
    
    // 将所有中心点加入队列
    for (int i = 0; i < numCenters; i++) {
        int r = centers[i].first;
        int c = centers[i].second;
        lake[r][c] = centerDepths[i];
        visited[r][c] = true;
        q.push({r, c});
    }
    
    // 方向数组
    int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
    int dc[] = {0, 1, 0, -1, -1, 1, -1, 1};
    
    // BFS扩散
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        for (int i = 0; i < 8; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !visited[nr][nc]) {
                // 根据距离和随机因素计算深度
                double minDistance = rows + cols;
                for (int j = 0; j < numCenters; j++) {
                    double distance = sqrt(pow(nr - centers[j].first, 2) + pow(nc - centers[j].second, 2));
                    minDistance = min(minDistance, distance);
                }
                
                // 深度随距离中心点距离增加而减小
                double depthFactor = max(0.0, 1.0 - minDistance / (min(rows, cols) / 2.0));
                
                // 添加随机扰动使湖更自然
                double randomFactor = 0.7 + 0.6 * dis(gen);
                
                // 计算最终深度
                int depth = static_cast<int>(lake[r][c] * depthFactor * randomFactor);
                
                // 确保深度在合理范围内
                depth = max(1, min(10, depth));
                
                // 有一定概率停止扩散（模拟湖的边界）
                if (dis(gen) < 0.85 || depth > 1) {
                    lake[nr][nc] = depth;
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }
    
    // 平滑处理 - 减少突变
    vector<vector<int>> smoothedLake = lake;
    for (int r = 1; r < rows-1; r++) {
        for (int c = 1; c < cols-1; c++) {
            if (lake[r][c] > 0) {
                int sum = 0;
                int count = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (lake[r+i][c+j] > 0) {
                            sum += lake[r+i][c+j];
                            count++;
                        }
                    }
                }
                smoothedLake[r][c] = sum / count;
            }
        }
    }
    
    return smoothedLake;
}

// 打印湖的二维数组
void printLake(const vector<vector<int>>& lake) {
    cout << "生成的湖二维数组 (" << lake.size() << "×" << lake[0].size() << "):" << endl;
    cout << "{" << endl;
    for (const auto& row : lake) {
        cout << "  {";
        for (int i = 0; i < row.size(); i++) {
            cout << row[i];
            if (i < row.size() - 1) cout << ", ";
        }
        cout << "}," << endl;
    }
    cout << "}" << endl;
}

// 可视化显示湖
void visualizeLake(const vector<vector<int>>& lake) {
    cout << "\n湖的可视化 (数字表示水深，0表示陆地):" << endl;
    for (const auto& row : lake) {
        for (int depth : row) {
            if (depth == 0) {
                cout << " . "; // 陆地
            } else if (depth <= 3) {
                cout << " \033[34m" << depth << "\033[0m "; // 浅蓝 - 浅水区
            } else if (depth <= 6) {
                cout << " \033[36m" << depth << "\033[0m "; // 青色 - 中等水深
            } else {
                cout << " \033[35m" << depth << "\033[0m "; // 紫色 - 深水区
            }
        }
        cout << endl;
    }
    cout << "图例: . = 陆地, 1-3 = 浅水, 4-6 = 中等, 7+ = 深水" << endl;
}

int main() {
    // 生成18×12的湖
    vector<vector<int>> lake = generateNaturalLake(18, 12);
    
    // 打印二维数组形式
    printLake(lake);
    
    // 可视化显示
    visualizeLake(lake);
    
    // 统计信息
    int totalWaterCells = 0;
    int totalDepth = 0;
    int maxDepth = 0;
    
    for (const auto& row : lake) {
        for (int depth : row) {
            if (depth > 0) {
                totalWaterCells++;
                totalDepth += depth;
                maxDepth = max(maxDepth, depth);
            }
        }
    }
    
    cout << "\n湖的统计信息:" << endl;
    cout << "水域面积: " << totalWaterCells << " 个单元格" << endl;
    cout << "最大水深: " << maxDepth << endl;
    cout << "平均水深: " << fixed << setprecision(2) 
         << (totalWaterCells > 0 ? static_cast<double>(totalDepth) / totalWaterCells : 0) << endl;
    cout << "水域覆盖率: " << fixed << setprecision(1) 
         << (static_cast<double>(totalWaterCells) / (18 * 12) * 100) << "%" << endl;
    
    return 0;
}