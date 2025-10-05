#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void permute(string str, int left, int right, vector<string> &result) {// 取引用保证结果传到数组
    if (left == right) {
        result.push_back(str);
    } else {
        for (int i = left; i <= right; i++) {
            swap(str[left], str[i]);// 逐次交换，swap交换函数
            permute(str, left + 1, right, result);// 利用void自结束回溯完成递归
            swap(str[left], str[i]);
        }
    }
}

int main() {
    string chars = "abcd";
    vector<string> permutations;
    
    permute(chars, 0, chars.length() - 1, permutations);
    sort(permutations.begin(), permutations.end());// sort保证字典序，需要<algotithm>头文件
                                                   // 该程序只保证全交换，不保证全字典序
    
    for (const auto &p : permutations) {
        cout << p << " ";
    }
    cout << endl;
    
    return 0;
}