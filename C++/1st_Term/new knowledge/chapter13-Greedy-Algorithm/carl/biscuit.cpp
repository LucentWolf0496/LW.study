// 贪心法，给胃口和饼干数组，优先用更大的饼干满足更大胃口的人
// 不用嵌套两层循环，而是维护“index”标记，表征当前最大没用的饼干，从而降低时间复杂度
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> g;// 胃口
    vector<int> s;// 饼干
    sort(g.begin(),g.end());
    sort(s.begin(),s.end());// from small to big，升序
    int huge = s.size() - 1;
    int result = 0;
    for (int i = g.size() - 1 ; i >= 0 ; i --){
        if (huge >= 0 && s[huge] >= g[i]){// 严防数组越界！！！先判断>=0防止越界再进行后续行动
            result ++;
            huge --;
        }
    }
    return result;
}