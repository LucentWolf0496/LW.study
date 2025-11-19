#include <iostream>
#include <string>
#include <vector>
using namespace std;// 多位大数互相相乘，需要巧妙算法，11位相乘得1位，12位相乘得2位，13位/22位相乘之和得3位……

int main() {
    string s1, s2;
    cin >> s1 >> s2;  
    if (s1 == "0" || s2 == "0") {// 处理特殊情况
        cout << "0" << endl;
        return 0;
    }
    
    int len1 = s1.size(), len2 = s2.size();
    vector<int> result(len1 + len2, 0);  // 结果最多为 len1+len2 位
    
    for (int i = len1 - 1; i >= 0; i--) {// 模拟竖式乘法，索引尽量简洁优雅
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (s1[i] - '0') * (s2[j] - '0');
            int sum = mul + result[i + j + 1];// 算法：先存多位数，再统一进位
            
            result[i + j + 1] = sum % 10;      // 当前位
            result[i + j] += sum / 10;         // 进位,及时处理进位
        }
    }
    
    int start = 0;// 找到第一个非零位
    while (start < result.size() && result[start] == 0) {
        start++;
    }
    
    if (start == result.size()) {// 输出结果
        cout << "0";  // 结果为0
    } else {
        for (int i = start; i < result.size(); i++) {
            cout << result[i];
        }
    }
    cout << endl;
    
    return 0;
}