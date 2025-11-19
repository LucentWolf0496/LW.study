#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<int> tianji(n), qiwang(n);
        
        // 读取田忌的马的速度
        for (int i = 0; i < n; i++) {
            cin >> tianji[i];
        }
        // 读取齐王的马的速度
        for (int i = 0; i < n; i++) {
            cin >> qiwang[i];
        }
        
        // 将马按速度从小到大排序
        sort(tianji.begin(), tianji.end());
        sort(qiwang.begin(), qiwang.end());
        
        int tianji_fast = n - 1;  // 田忌最快的马
        int tianji_slow = 0;      // 田忌最慢的马
        int qiwang_fast = n - 1;  // 齐王最快的马
        int qiwang_slow = 0;      // 齐王最慢的马
        
        int money = 0;  // 田忌获得的钱数
        
        // 进行n场比赛
        for (int i = 0; i < n; i++) {
            // 如果田忌最快的马比齐王最快的马快
            if (tianji[tianji_fast] > qiwang[qiwang_fast]) {
                money += 200;
                tianji_fast--;
                qiwang_fast--;
            }
            // 如果田忌最快的马比齐王最快的马慢
            else if (tianji[tianji_fast] < qiwang[qiwang_fast]) {
                money -= 200;
                tianji_slow++;
                qiwang_fast--;
            }
            // 如果最快的马速度相等
            else {
                // 如果田忌最慢的马比齐王最慢的马快
                if (tianji[tianji_slow] > qiwang[qiwang_slow]) {
                    money += 200;
                    tianji_slow++;
                    qiwang_slow++;
                }
                // 否则用田忌最慢的马对齐王最快的马
                else {
                    if (tianji[tianji_slow] < qiwang[qiwang_fast]) {
                        money -= 200;
                    }
                    tianji_slow++;
                    qiwang_fast--;
                }
            }
        }
        
        cout << money << endl;
    }
    
    return 0;
}