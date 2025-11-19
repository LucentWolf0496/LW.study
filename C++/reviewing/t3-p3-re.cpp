#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 破题核心依旧是对于time变量的描述
// 诊断一个病人就+10time
// 遇到空档期就将time更新为下一个病人到来时的时间
// 判断结束就是time > 170

// 数组题目总是要尤其小心索引！！！！！

int main(){
    int n = 0;
    cin >> n;
    vector<int> time(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> time[i];
    }
    int time0 = 60;
    int count = 0;
    sort(time.begin() , time.end());// sort&<algorithm>简化，一步到位！但是带结构体还是得老老实实冒泡以对整个结构体易位
    for (int i = 0 ; i < n ; i ++){
        if (time[i] > time0)
            time0 = time[i];
        if (time0 + 10 <= 180){
            time0 += 10;
            count ++;
        }
        else
            break;
    }
    cout << count << endl;
}