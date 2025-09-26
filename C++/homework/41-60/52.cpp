#include <iostream>
#include <vector>
using namespace std;

int main(){
    struct point{
        int x;
        int y;
    };
    int n = 0;
    cin >> n;
    vector<int> num;
    for (int i = 1 ; i <= 2 * n ; i ++){
        int temp = 0;
        cin >> temp;
        num.push_back(temp);
    }
    vector<point> poi;
    for (int i = 0 ; i < n ; i ++){
        poi.push_back({num[i * 2] , num[i * 2 + 1]});
    }
    for (int i = 1 ; i < n ; i ++){
        for (int j = 0 ; j < n - i ; j ++){
            if (poi[j].x > poi[j + 1].x){
                point temp = poi[j];
                poi[j] = poi [j + 1];
                poi[j + 1] = temp;
            }
        }
    }
    for (int i = 0 ; i < poi.size() ; i ++){// 修改擦除模块——4个要点
        for (int j = 0 ; j < poi.size() ; j ++){// 要点1：j也要从0开始遍历
            if (j == i) continue;// 要点2：continue掉自己的擦除
            if (poi[i].x <= poi[j].x && poi[i].y <= poi[j].y){
                poi.erase(poi.begin() + i);
                i --;// 要点3：i--保证擦除之后不错位
                break;// 要点4：检测到对应j之后退出第二循环，进行i++的第一循环
            }
        }
    }
    cout << "(" << poi[0].x << "," << poi[0].y << ")";
    for (int i = 1 ; i < poi.size() ; i ++){
        cout << "," << "(" << poi[i].x << "," << poi[i].y << ")";
    }
    cout << endl;
    return 0;
}