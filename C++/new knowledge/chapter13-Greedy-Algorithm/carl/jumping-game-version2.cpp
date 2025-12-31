// 重写一遍奶牛监控问题
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<int> list(n);
    vector<int> maxdis(n , 0);// 相对于跳跃游戏，需要额外预存监控最远点！
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
        int start = max(0 , i - list[i]);
        maxdis[start] = max(maxdis[start] , i + list[i]);
    }

    int result = 0;
    int nowmax = 0;
    int max1 = 0;
    for (int i = 0 ; i < n ; i ++){
        nowmax = max(nowmax , maxdis[i]);
        if (i > max1){// 监控是走出圈再安装，跳跃是到圈的边缘就要跳，分析好区别
            result ++;
            max1 = nowmax;
            if (max1 >= n - 1) break;// 已经可以完全监控
        }
    }
    cout << result << endl;
}