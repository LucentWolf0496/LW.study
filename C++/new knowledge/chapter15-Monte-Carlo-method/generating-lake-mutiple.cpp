#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

// 生成多个符合自然规律的湖，包含陆地
vector<vector<int>> generateMultipleLakes(int rows, int cols) {
    vector<vector<int>> terrain(rows, vector<int>(cols, 0)); // 初始化为全陆地
    
    // 随机数生成器
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> numLakesDist(3, 5); // 生成3-5个湖
    uniform_int_distribution<> centerRowDist(2, rows-3);
    uniform_int_distribution<> centerColDist(2, cols-3);
    uniform_real_distribution<> probDist(0.0, 1.0);
    
    int numLakes = numLakesDist(gen);
    cout << "生成 " << numLakes << " 个湖" << endl;
    
    // 存储所有湖的中心点
    vector<pair<int, int>> lakeCenters;
    
    // 生成湖的中心点，确保它们不会太接近
    for (int i = 0; i < numLakes; i++) {
        int attempts = 0;
        bool validPosition = false;
        
        while (!validPosition && attempts < 100) {
            int r = centerRowDist(gen);
            int c = centerColDist(gen);
            
            // 检查是否与已有中心点保持足够距离
            validPosition = true;
            for (const auto& center : lakeCenters) {
                double distance = sqrt(pow(r - center.first, 2) + pow(c - center.second, 2));
                if (distance < min(rows, cols) / 3.0) { // 至少保持1/3网格大小的距离
                    validPosition = false;
                    break;
                }
            }
            
            if (validPosition) {
                lakeCenters.push_back({r, c});
                break;
            }
            attempts++;
        }
    }
    
    // 为每个湖生成不同的参数
    vector<int> lakeMaxDepths;
    vector<double> lakeSizes;
    
    for (int i = 0; i < numLakes; i++) {
        lakeMaxDepths.push_back(8 + gen() % 5); // 最大深度8-12
        lakeSizes.push_back(0.3 + 0.3 * probDist(gen)); // 湖的大小因子0.3-0.6
    }
    
    // 为每个湖分别进行扩散
    for (int lakeIdx = 0; lakeIdx < numLakes; lakeIdx++) {
        int centerR = lakeCenters[lakeIdx].first;
        int centerC = lakeCenters[lakeIdx].second;
        int maxDepth = lakeMaxDepths[lakeIdx];
        double sizeFactor = lakeSizes[lakeIdx];
        
        // 使用BFS从中心点向外扩散
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        queue<pair<int, int>> q;
        
        // 设置中心点深度
        terrain[centerR][centerC] = maxDepth;
        visited[centerR][centerC] = true;
        q.push({centerR, centerC});
        
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
                    // 计算到中心点的距离
                    double distance = sqrt(pow(nr - centerR, 2) + pow(nc - centerC, 2));
                    
                    // 根据距离和湖的大小因子决定是否继续扩散
                    double maxDistance = min(rows, cols) * sizeFactor;
                    if (distance > maxDistance) continue;
                    
                    // 深度随距离中心点距离增加而减小
                    double depthFactor = max(0.0, 1.0 - distance / maxDistance);
                    
                    // 添加随机扰动使湖更自然
                    double randomFactor = 0.7 + 0.6 * probDist(gen);
                    
                    // 计算最终深度
                    int depth = static_cast<int>(maxDepth * depthFactor * randomFactor);
                    
                    // 确保深度在合理范围内
                    depth = max(1, min(maxDepth, depth));
                    
                    // 如果当前位置已经是其他湖的一部分，选择较深的值
                    if (terrain[nr][nc] > 0) {
                        terrain[nr][nc] = max(terrain[nr][nc], depth);
                    } else {
                        terrain[nr][nc] = depth;
                    }
                    
                    // 有一定概率停止扩散（模拟湖的边界）
                    if (probDist(gen) < 0.8 || depth > 2) {
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
        }
    }
    
    // 平滑处理 - 减少突变
    vector<vector<int>> smoothedTerrain = terrain;
    for (int r = 1; r < rows-1; r++) {
        for (int c = 1; c < cols-1; c++) {
            if (terrain[r][c] > 0) {
                int sum = 0;
                int count = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (terrain[r+i][c+j] > 0) {
                            sum += terrain[r+i][c+j];
                            count++;
                        }
                    }
                }
                if (count > 0) {
                    smoothedTerrain[r][c] = sum / count;
                }
            }
        }
    }
    
    return smoothedTerrain;
}

// 打印地形二维数组
void printTerrain(const vector<vector<int>>& terrain) {
    cout << "生成的地形二维数组 (" << terrain.size() << "×" << terrain[0].size() << "):" << endl;
    cout << "{" << endl;
    for (const auto& row : terrain) {
        cout << "  {";
        for (int i = 0; i < row.size(); i++) {
            cout << row[i];
            if (i < row.size() - 1) cout << ", ";
        }
        cout << "}," << endl;
    }
    cout << "}" << endl;
}

// 可视化显示地形
void visualizeTerrain(const vector<vector<int>>& terrain) {
    cout << "\n地形可视化 (数字表示水深，0表示陆地):" << endl;
    for (const auto& row : terrain) {
        for (int depth : row) {
            if (depth == 0) {
                cout << " \033[32m.\033[0m "; // 绿色 - 陆地
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
    cout << "图例: \033[32m.\033[0m = 陆地, \033[34m1-3\033[0m = 浅水, \033[36m4-6\033[0m = 中等, \033[35m7+\033[0m = 深水" << endl;
}

// 分析湖的统计信息
void analyzeLakes(const vector<vector<int>>& terrain) {
    int rows = terrain.size();
    int cols = terrain[0].size();
    
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<pair<int, int>>> lakes;
    
    // 方向数组
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};
    
    // 查找所有湖
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (terrain[i][j] > 0 && !visited[i][j]) {
                // 使用BFS标记整个湖
                vector<pair<int, int>> lake;
                queue<pair<int, int>> q;
                
                q.push({i, j});
                visited[i][j] = true;
                
                while (!q.empty()) {
                    auto [r, c] = q.front();
                    q.pop();
                    
                    lake.push_back({r, c});
                    
                    for (int d = 0; d < 4; d++) {
                        int nr = r + dr[d];
                        int nc = c + dc[d];
                        
                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && 
                            terrain[nr][nc] > 0 && !visited[nr][nc]) {
                            visited[nr][nc] = true;
                            q.push({nr, nc});
                        }
                    }
                }
                
                lakes.push_back(lake);
            }
        }
    }
    
    // 输出湖的统计信息
    cout << "\n湖的统计信息:" << endl;
    cout << "发现 " << lakes.size() << " 个湖" << endl;
    
    for (int i = 0; i < lakes.size(); i++) {
        int area = lakes[i].size();
        int totalDepth = 0;
        int maxDepth = 0;
        
        for (const auto& cell : lakes[i]) {
            int depth = terrain[cell.first][cell.second];
            totalDepth += depth;
            maxDepth = max(maxDepth, depth);
        }
        
        double avgDepth = static_cast<double>(totalDepth) / area;
        
        cout << "湖 " << i+1 << ": 面积=" << area 
             << ", 最大水深=" << maxDepth
             << ", 平均水深=" << fixed << setprecision(2) << avgDepth << endl;
    }
}

int main() {
    // 生成18×12的地形，包含多个湖和陆地
    vector<vector<int>> terrain = generateMultipleLakes(18, 12);
    
    // 打印二维数组形式
    printTerrain(terrain);
    
    // 可视化显示
    visualizeTerrain(terrain);
    
    // 分析湖的统计信息
    analyzeLakes(terrain);
    
    return 0;
}