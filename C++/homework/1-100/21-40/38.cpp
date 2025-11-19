#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

int main()// 结构数组处理输出！
{
    int n = 0;
    cin >> n;
    int k = n * (n - 1) / 2;
    vector<vector<int>> point;// 意思是point数组的元素类型是数组！！
    struct result{
        int x1;
        int y1;
        int z1;
        int x2;
        int y2;
        int z2;
        float sum;
    };
    vector<result> room;// 记得设置vector-以result作为变量类型
    for (int i = 1 ; i <= n ; i ++){
        int a = 0 , b = 0 , c = 0;
        cin >> a >> b >> c;
        point.push_back({a , b , c});// 直接push动态添加三元数组元素到point里面
    }
    for (int i = 1 ; i <= n ; i ++){
        for (int j = i + 1 ; j <= n ; j ++){
            float dist = 0.0;
            float x = point[i - 1][0] - point[j - 1][0];
            float y = point[i - 1][1] - point[j - 1][1];
            float z = point[i - 1][2] - point[j - 1][2];
            dist = sqrt(x * x + y * y + z * z);
            room.push_back({point[i - 1][0] , point[i - 1][1] , point[i - 1][2] , point[j - 1][0] , point[j - 1][1] , point[j - 1][2] , dist});
        }
    }
    for (int i = 1 ; i <= k - 1 ; i ++){
        for (int j = 0 ; j <= k - 1 - i ; j ++){
            if (room[j].sum < room[j + 1].sum){
                result temp = room[j];// 对room数组的所有result内的单个变量排序
                                      // 但对所有的整个result类型变量更改顺序！！！
                room[j] = room[j + 1];
                room[j + 1] = temp;
            }
        }
    }
    for (int i = 0 ; i < k ; i ++){
        cout << "(" << room[i].x1 << "," << room[i].y1 << "," << room[i].z1 << ")-(" << room[i].x2 << "," << room[i].y2 << "," << room[i].z2 << ")=" << fixed << setprecision(2) << room[i].sum << endl;
    }
    return 0;
}