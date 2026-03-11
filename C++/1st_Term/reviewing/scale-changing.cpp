// 位数过多int甚至double都存不下？
// 就用直接的，单位次递归来转进制！！！
// 先进位递归转10，后由10转目标进制（套路题）
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

int f(char x){// 将字符数字化
    if (x >= '0' && x <= '9')
        return x - '0';
    else if (x >= 'A' && x <= 'Z')
        return x - 'A' + 10;
    else
        return x - 'a' + 10;
}

char f1(int x){// 将数字字符化
    if (x >= 0 && x <= 9)
        return '0' + x;
    else
        return 'A' + (x - 10);
}

// 将a进制字符串转换为10进制数（用vector存储，避免溢出）
vector<int> convertToDecimal(const string& s, int a) {
    vector<int> decimal;
    if (s.empty()) return decimal;
    
    // 初始化：第一个数字
    decimal.push_back(f(s[0]));
    
    for (int i = 1; i < s.length(); i++) {
        int current = f(s[i]);
        
        // 乘以基数a
        int carry = 0;
        for (int j = 0; j < decimal.size(); j++) {
            int temp = decimal[j] * a + carry;
            decimal[j] = temp % 10;
            carry = temp / 10;
        }
        
        // 处理剩余的进位
        while (carry > 0) {
            decimal.push_back(carry % 10);
            carry /= 10;
        }
        
        // 加上当前位
        carry = current;
        for (int j = 0; j < decimal.size() && carry > 0; j++) {
            int temp = decimal[j] + carry;
            decimal[j] = temp % 10;
            carry = temp / 10;
        }
        
        while (carry > 0) {
            decimal.push_back(carry % 10);
            carry /= 10;
        }
    }
    
    return decimal;
}

// 将10进制数转换为b进制字符串
string convertFromDecimal(vector<int> decimal, int b) {
    if (decimal.empty()) return "0";
    
    string result;
    vector<int> quotient;
    
    // 当decimal不为0时继续转换
    while (!decimal.empty()) {
        // 模拟除法：decimal除以b
        int remainder = 0;
        quotient.clear();
        
        // 从高位到低位进行除法
        for (int i = decimal.size() - 1; i >= 0; i--) {// 注意索引！上个函数没有倒序，故此时后高位前低位
            int current = remainder * 10 + decimal[i];
            if (!quotient.empty() || current >= b) {
                quotient.push_back(current / b);
            }
            remainder = current % b;
        }
        
        // 余数就是当前位的值
        result.push_back(f1(remainder));
        
        // 商作为新的被除数
        decimal = quotient;
        reverse(decimal.begin(), decimal.end());
    }
    
    // 反转结果，因为我们是先得到低位
    reverse(result.begin(), result.end());
    return result;
}

int main(){
    int n = 0;
    cin >> n;
    cin.ignore();

    for (int x = 0 ; x < n ; x ++){
        int a , b;
        string s , s1;
        getline(cin , s1);
        
        // 替换逗号为空格
        for (int i = 0 ; i < s1.size() ; i ++){
            if (s1[i] == ',')
                s1[i] = ' ';
        }
        
        // 使用stringstream解析输入
        stringstream ss1(s1);
        ss1 >> a >> s >> b;

        // 转换为10进制
        vector<int> decimal = convertToDecimal(s, a);
        
        // 转换为目标进制
        string result = convertFromDecimal(decimal, b);
        
        cout << result << endl;
    }
    return 0;
}