#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// 核心：dp算出与0的间距
// 递归，以O(n)复杂度计算间距。防止每次计算最短间距还要再套一层循环达到O(n ^ 3)的复杂度
// 先算好就只需要O(n ^ 2)的复杂度

// 数组题目总是要尤其小心索引！！！！！

int main(){
    int n = 0;
    cin >> n;
    vector<int> wine(n);
    vector<int> distance(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> wine[i] >> distance[i];
    }
    vector<int> d(n , 0);
    for (int i = 1 ; i < n ; i ++){
        d[i] = distance[i - 1] + d[i - 1];
    }
    int cycle = d[n - 1] + distance[n - 1];

    long long result = LLONG_MAX; // 数据太大要用long long，精度需要求大要用double甚至long double（虽然这题int也行hhh
    int index = 0;
    for (int i = 0 ; i < n ; i ++){
        long long temp = 0;// 一定要注意循环内temp变量的初始化问题！！！
        for (int j = 0 ; j < n ; j ++){
            if (i == j) continue;
            int shun = 0;
            int ni = 0;
            int dis = 0;
            if (i > j){
                ni = d[i] - d[j];
                shun = cycle - d[i] + d[j];
                dis = (shun > ni ? ni : shun);
            }
            else if (i < j){
                shun = d[j] - d[i];
                ni = cycle - d[j] + d[i];
                dis = (shun > ni ? ni : shun);
            }
            temp += dis * wine[j];
        }
        if (temp < result){
            index = i;
            result = temp;
        }
    }

    cout << index << "," << result << endl;
}