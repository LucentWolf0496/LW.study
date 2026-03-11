#include <iostream>
#include <unordered_set>// 借助完美的头文件，以极小的时间复杂度完成任务
#include <vector>
using namespace std;// 当然，核心依旧是贪心法思维，建议去预习一下

int main(){
    int n = 0 , m = 0;
    cin >> n >> m;
    vector<int> list(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    unordered_set<int> temp;// 这个头文件下的temp自动去重！！！所以可以实现“找且仅找一轮”
    int count = 0;
    for (int i = 0 ; i < n ; i ++){
        temp.insert(list[i]);
        if (temp.size() == m){
            count ++;
            temp.clear();// 贪心法：每找一轮所有数码就清空&加1，表示序列最大长度可以加一，因为必然可找全序列全排
        }
    }
    cout << count + 1 << endl;// 记得加1
}