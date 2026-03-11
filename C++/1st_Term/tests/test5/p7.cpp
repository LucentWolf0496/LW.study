#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    // 预处理：对于每个左端点L，记录能到达的最大右端点
    vector<int> maxRightAtLeft(n + 2, 0);  // n+2防止越界
    for (int i = 1; i <= n; i++) {
        int L = max(1, i - a[i]);
        int R = min(n, i + a[i]);
        maxRightAtLeft[L] = max(maxRightAtLeft[L], R);
    }
    
    int covered = 0;      // 当前已覆盖到的最右位置
    int nextCover = 0;    // 下一步能覆盖到的最右位置
    int cameras = 0;      // 摄像头数量
    
    for (int i = 1; i <= n; i++) {
        // 更新下一步能覆盖到的最远位置
        nextCover = max(nextCover, maxRightAtLeft[i]);
        
        // 如果当前位置正好是已覆盖区域的边界+1
        if (i > covered) {
            cameras++;
            covered = nextCover;
            
            // 如果已经覆盖到终点，提前结束
            if (covered >= n) break;
        }
    }
    
    cout << cameras << endl;
    return 0;
}