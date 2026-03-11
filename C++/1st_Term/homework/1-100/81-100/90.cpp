#include <iostream>
#include <vector>
using namespace std;// 凑单问题：正向累加优于反向减去，采用更直接的思维方式

int final = 0;
int rule = 0;

void get(vector<bool> check, vector<int> list, int result) {
    int num = list.size();
    
    // 检查当前结果是否满足条件并更新最优解
    if (result >= rule) {
        if (result < final) {
            final = result;
        }
    }
    
    // 遍历所有商品
    for (int i = 0; i < num; i++) {
        if (!check[i]) {
            check[i] = true;
            // 递归调用，注意这里应该是加上商品价格，而不是减去
            get(check, list, result + list[i]);
            check[i] = false;
        }
    }
}

int main() {
    int num, money;
    cin >> num >> money;
    vector<int> list(num);
    for (int i = 0; i < num; i++) {
        cin >> list[i];
    }
    
    int total = 0;
    for (int i = 0; i < num; i++) {
        total += list[i];
    }
    
    if (total < money) {
        cout << 0 << endl;
    } else {
        rule = money;
        final = total + 1; // 初始化为一个较大的值
        
        vector<bool> check(num, false);
        // 从0开始递归，表示初始没有选中任何商品
        get(check, list, 0);
        
        // 如果final没有被更新，说明无法凑单
        if (final == total + 1) {
            cout << 0 << endl;
        } else {
            cout << final << endl;
        }
    }

    return 0;
}