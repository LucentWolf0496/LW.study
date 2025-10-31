#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> demand(n);      // 每个居民点的啤酒需求量
    vector<int> distance(n);    // 每个居民点到下一个居民点的距离
    vector<int> prefix(n);      // 前缀和，记录从0号点到各点的顺时针距离
    
    // 读取输入数据
    for (int i = 0; i < n; i++) {
        cin >> demand[i] >> distance[i];
    }
    
    // 计算前缀和：从0号点顺时针到各点的距离
    prefix[0] = 0;
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i-1] + distance[i-1];
    }
    int totalDistance = prefix[n-1] + distance[n-1]; // 环的总长度
    
    long long minCost = LLONG_MAX;
    int bestLocation = 0;
    
    // 遍历每个可能的建厂位置
    for (int factory = 0; factory < n; factory++) {
        long long totalCost = 0;
        
        // 计算从工厂到每个居民点的运输费用
        for (int i = 0; i < n; i++) {
            if (i == factory) continue; // 工厂所在地不需要运输
            
            // 计算顺时针距离
            int clockwiseDist;
            if (i > factory) {
                clockwiseDist = prefix[i] - prefix[factory];
            } else {
                clockwiseDist = prefix[i] + (totalDistance - prefix[factory]);
            }
            
            // 计算逆时针距离
            int anticlockwiseDist = totalDistance - clockwiseDist;
            
            // 取较短距离
            int minDist = min(clockwiseDist, anticlockwiseDist);
            
            // 累加运输费用
            totalCost += (long long)demand[i] * minDist;
        }
        
        // 更新最小费用和最佳位置
        if (totalCost < minCost) {
            minCost = totalCost;
            bestLocation = factory;
        }
    }
    
    cout << bestLocation << "," << minCost << endl;
    
    return 0;
}