#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};

int main() {
    struct dot {
        int x;
        int y;
        int last;  // 上一个方向
        int count; // 线段数
    };
    
    int board_count = 0;
    int w, h;
    
    while (cin >> w >> h) {
        if (w == 0 && h == 0)
            return 0;
        
        board_count++;
        cout << "Board #" << board_count << ":" << endl;
        
        // 创建扩展的棋盘，四周留空，允许路径离开矩形板
        vector<vector<char>> table(h + 2, vector<char>(w + 2, ' '));
        
        // 读取棋盘数据，注意坐标转换
        string line;
        getline(cin, line); // 读取换行符
        for (int i = 1; i <= h; i++) {
            getline(cin, line);
            for (int j = 1; j <= w; j++) {
                if (j-1 < line.length()) {
                    table[i][j] = line[j-1];
                }
            }
        }
        
        int x1, y1, x2, y2;
        int pair_count = 0;
        
        while (cin >> x1 >> y1 >> x2 >> y2) {
            if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0)
                break;
            
            pair_count++;
            cout << "Pair " << pair_count << ": ";
            
            // 如果起点或终点没有卡片或者位置相同
            if (table[y1][x1] != 'X' || table[y2][x2] != 'X') {
                cout << "impossible." << endl;
                continue;
            }
            
            // 使用三维数组记录访问状态和最小线段数 [y][x][direction]
            vector<vector<vector<int>>> visited(h + 2, 
                vector<vector<int>>(w + 2, 
                vector<int>(4, 100000)));
            
            queue<dot> q;
            int min_segments = 100000;
            
            // 从起点开始，初始方向为-1，线段数为0
            for (int i = 0; i < 4; i++) {
                q.push({x1, y1, i, 0});
                visited[y1][x1][i] = 0;
            }
            
            while (!q.empty()) {
                dot current = q.front();
                q.pop();
                
                int tx = current.x;
                int ty = current.y;
                int tlast = current.last;
                int tcount = current.count;
                
                // 如果到达终点，更新最小线段数
                if (tx == x2 && ty == y2) {
                    min_segments = min(min_segments, tcount);
                    continue;
                }
                
                for (int i = 0; i < 4; i++) {
                    int nx = tx + dx[i];
                    int ny = ty + dy[i];
                    
                    // 检查边界
                    if (nx < 0 || nx > w + 1 || ny < 0 || ny > h + 1)
                        continue;
                    
                    // 检查是否可以通行（空格或者终点）
                    if (table[ny][nx] != ' ' && !(nx == x2 && ny == y2))
                        continue;
                    
                    int new_count = tcount;
                    if (i != tlast) {
                        new_count = tcount + 1;
                    }
                    
                    // 如果找到更短的路径，更新并继续搜索
                    if (new_count < visited[ny][nx][i]) {
                        visited[ny][nx][i] = new_count;
                        q.push({nx, ny, i, new_count});
                    }
                }
            }
            
            if (min_segments < 100000) {
                // 线段数需要+1，因为从起点开始就算第一个线段
                cout << min_segments + 1 << " segments." << endl;
            } else {
                cout << "impossible." << endl;
            }
        }
        cout << endl;
    }
    return 0;
}