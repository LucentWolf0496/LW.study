// 多个考虑维度的贪心法：糖果分发
// 需要从左边/右边遍历数组，得出左边和右边均可以满足的糖果数目
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<int> ratings(n , 0);
    for (int i = 0 ; i < n ; i ++){
        cin >> ratings[i];
    }
    int result = 0;
    vector<int> greedy(n , 1);// 贪心数组初始化：每个孩子至少分到一个糖果
    for (int i = 1 ; i < n ; i ++){// 从左往右遍历，仅考虑左边的大小比较
        if (ratings[i] > ratings[i - 1]) greedy[i] = greedy[i - 1] + 1;
    }
    for (int i = n - 2 ; i >= 0 ; i --){// 从右往左遍历，但是保证从左边也要满足，所以取max值
        if (ratings[i] > ratings[i + 1]) greedy[i] = max(greedy[i] , greedy[i + 1] + 1);
    }
    for (int i = 0 ; i < n ; i ++){
        result += greedy[i];
    }
    cout << result << endl;
}