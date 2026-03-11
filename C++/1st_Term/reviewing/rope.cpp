#include <iostream>
#include <vector>
using namespace std;
// 关键点：对于时间变量的记录
// 记录每次跳坏恢复的时间，如果大于63就用60减去之前所有跳坏次数和，如果在60-63就是跳坏时的计数
// 注意以上两种情况都需要break掉
// 如果跳坏最后一次恢复仍旧在60s之内？就是60-跳坏总次数*3，设为count的初始值即可

// 数组题目总是要尤其小心索引！！！！！

int main(){
    int n = 0;
    cin >> n;
    for (int i = 0 ; i < n ; i ++){
        int m = 0;
        cin >> m;
        vector<int> bad(m);
        for (int j = 0 ; j < m ; j ++){
            cin >> bad[j];
        }
        int time = 0;
        int count = 60 - bad.size() * 3;// 基础数值，有全无效或半无效跳坏才更新，否则直接输出
        for (int j = 0 ; j < m ; j ++){
            time = bad[j] + (j + 1) * 3;// 恢复后的时间
            if (time - 3 > 60){
                count = 60 - 3 * j;// 此次跳坏在63s之后，完全无效
                break;
            }
            else if (time - 3 <= 60 && time >= 60){// 半无效跳坏，可以根据跳坏计数直接读出结果
                count = bad[j];
                break;
            }
        }
        cout << count << endl;
    }
    return 0;
}