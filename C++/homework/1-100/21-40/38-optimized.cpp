#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>  // 添加algorithm头文件用于sort函数
using namespace std;

int main()
{
    int n;
    cin >> n;
    
    // 定义点结构体，更清晰
    struct Point {
        int x, y, z;
    };
    
    // 定义结果结构体-嵌套点结构体，简化！！！
    struct Result {
        Point p1, p2;
        float distance;
    };
    
    vector<Point> points;
    vector<Result> results;
    
    // 输入点坐标
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        points.push_back({x, y, z});
    }
    
    // 计算所有点对之间的距离
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float dx = points[i].x - points[j].x;
            float dy = points[i].y - points[j].y;
            float dz = points[i].z - points[j].z;
            float dist = sqrt(dx*dx + dy*dy + dz*dz);
            
            results.push_back({points[i], points[j], dist});
        }
    }
    
    // 使用STL排序替代冒泡排序（视题目要求而定，有些顺序要求直接冒泡更好！）
    sort(results.begin(), results.end(), [](const Result& a, const Result& b) {
        return a.distance > b.distance;  // 降序排列
    });
    
    // 输出结果
    for (const auto& res : results) {
        cout << "(" << res.p1.x << "," << res.p1.y << "," << res.p1.z << ")-"
             << "(" << res.p2.x << "," << res.p2.y << "," << res.p2.z << ")="
             << fixed << setprecision(2) << res.distance << endl;// 双重.结构体引用，提取结构嵌套结构的数据
    }
    
    return 0;
}