#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> List; // 存储去重后的音符序列
vector<int> dp;
vector<int> pos;  // 维护最近出现的不同音符的位置 (类似LRU缓存)

int main(){
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    
    // 1-based indexing 占位
    List.push_back(0); 

    int last_val = -1;
    for (int i = 1, tmp; i <= n; i++){
        cin >> tmp;
        if (tmp == last_val) continue;
        List.push_back(tmp);
        last_val = tmp;
    }
    n = List.size() - 1; 
    dp.resize(n + 1);
    dp[0] = 0;
    // 初始化 pos，加入 0 作为哨兵，代表序列的起点
    pos.push_back(0);
    int limit = sqrt(n) + 2; 

    for (int i = 1; i <= n; i++){
        dp[i] = 2e9; // 初始化为无穷大

        // --- 1. 维护 pos 数组 (LRU 逻辑) ---
        
        // 在 pos 中查找当前音符 List[i] 是否已经存在
        int found_idx = -1;
        for(int j = 0; j < pos.size(); ++j){
            if(pos[j] == 0) continue; // 0 是哨兵，没有对应音符
            if(List[pos[j]] == List[i]){
                found_idx = j;
                break;
            }
        }

        // 如果找到了，先删除旧的位置
        if(found_idx != -1){
            pos.erase(pos.begin() + found_idx);
        }

        // 将当前位置插入到 pos 的最前面 (表示最近出现)
        pos.insert(pos.begin(), i);

        // 如果超过了 sqrt(N) 的限制，移除最久远的记录
        if(pos.size() > limit){
            pos.pop_back();
        }

        // --- 2. 状态转移 ---
        
        // pos[0] 是当前的 i。
        // pos[1] 是上一个不同音符的位置。如果我们从 pos[1] 切分：
        //   前一组结束于 pos[1]，当前组范围是 (pos[1], i]。
        //   由于 pos 记录了最近的不同音符，(pos[1], i] 这段区间内只有 1 种不同音符 (即 List[i] 本身)。
        //   代价 = dp[pos[1]] + 1*1。
        
        // 同理，如果我们从 pos[k] 切分：
        //   当前组范围 (pos[k], i]。
        //   这段区间内恰好包含 k 种不同的音符。
        //   代价 = dp[pos[k]] + k*k。

        for(int k = 1; k < pos.size(); ++k){
            int prev_idx = pos[k];
            // 转移方程：前一组的最小代价 + 当前组的代价(k^2)
            dp[i] = min(dp[i], dp[prev_idx] + k * k);
        }
    }

    cout << dp[n] << endl;
    return 0;
}