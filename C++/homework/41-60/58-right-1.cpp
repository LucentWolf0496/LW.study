#include <iostream>
#include <string>
using namespace std;// 一位一位处理而非直接一口吞掉2/3位
                    // 逐位处理便于余数变量remainder递归增加
                    // for循环便捷逐位亦可杜绝分类讨论2/3位的繁杂情况

int main() {
    string s;
    cin >> s;
    string result;
    int remainder = 0;  // 余数
    
    // 模拟竖式除法
    for (int i = 0; i < s.length(); i++) {
        int current = remainder * 10 + (s[i] - '0');
        int quotient = current / 13;
        remainder = current % 13;
        
        // 避免在结果开头添加前导零
        if (!result.empty() || quotient != 0) {
            result.push_back(quotient + '0');  // 正确转换为字符
        }
    }
    
    // 如果结果是空字符串，说明商为0
    if (result.empty()) {
        result = "0";
    }
    
    cout << result << endl;
    cout << remainder << endl;
    
    return 0;
}