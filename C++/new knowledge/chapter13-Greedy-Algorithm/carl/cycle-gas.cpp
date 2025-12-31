// 环形加油站找可行解，保证解的唯一性
// 一整圈油量小于油耗必然不行，大于等于则可能可行
// 贪心思维：从0开始累加剩余油量，一旦在索引i小于0，则需要更新起点为i+1
// （就算是旧的起点加完所有正数都会小于0，旧起点到i就都不行了）
// 最后保留的起点就是可行的起点
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<int> gas(n);
    vector<int> cost(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> gas[i] >> cost[i];
    }
    int start = 0;
    int gas_sum = 0;
    int cost_sum = 0;
    int cur_gas = 0;
    for (int i = 0 ; i < n ; i ++){
        gas_sum += gas[i];
        cost_sum += cost[i];
        cur_gas += gas[i] - cost[i];
        if (cur_gas < 0){
            start = i + 1;
            cur_gas = 0;
        }
    }
    if (gas_sum < cost_sum) cout << -1 << endl; 
    else cout << start << endl;
}
