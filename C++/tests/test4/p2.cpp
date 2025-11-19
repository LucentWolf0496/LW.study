#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> table(n, vector<int>(m));   
    vector<int> date(k + 1, 0);  // 第0天不用，从第1天开始
    
    // 读取输入
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> table[i][j];
        }
    }
    
    // 统计每天需要准备的考试场数
    for (int day = 1; day <= k; day++) {
        vector<bool> examUsed(m + 1, false);  // 记录当天哪些考试题已经被使用
        
        // 遍历每个学生
        for (int i = 0; i < n; i++) {
            // 遍历该学生的每套题
            for (int j = 0; j < m; j++) {
                // 如果这个学生在day天做第j套题
                if (table[i][j] == day) {
                    examUsed[j] = true;  // 标记这套题需要在当天准备
                    break;  // 每个学生在同一天只做一套题，找到后跳出内层循环
                }
            }
        }
        
        // 统计当天需要准备多少场考试
        for (int j = 0; j < m; j++) {
            if (examUsed[j]) {
                date[day]++;
            }
        }
    }
    
    // 输出结果
    cout << date[1];
    for (int i = 2; i <= k; i++) {
        cout << " " << date[i];
    }
    cout << endl;
    
    return 0;
}