#include <iostream>
#include <string>
using namespace std;// 高进度运算迭代过程中的索引问题！！！

string add(string num1, string num2) {
    if (num1.size() < num2.size()) {
        string temp = num1;
        num1 = num2;
        num2 = temp;
    }

    while (num2.size() < num1.size()) {
        num2 = "0" + num2;// 通过添加前导0强行拉平size，从而规避索引分段考虑，一步到位
    }
    
    int carry = 0;
    string result;
    
    for (int i = num1.size() - 1; i >= 0; i--) {
        int digit1 = num1[i] - '0';
        int digit2 = num2[i] - '0';
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        sum %= 10;
        char digit_char = sum + '0';
        result.push_back(digit_char);
    }
    
    while (carry > 0) {
        char digit_char = carry % 10 + '0';
        result.push_back(digit_char);
        carry /= 10;
    }
    
    string final_result;
    for (int i = result.size() - 1; i >= 0; i--) {
        final_result.push_back(result[i]);
    }
    return final_result;
}

string kick(string num1, string num2) {
    bool negative = false;
    if (num1.size() < num2.size() || (num1.size() == num2.size() && num1 < num2)) {
        negative = true;
        swap(num1, num2);// 强制改序并添加负数标记，最后输出负号即可
    }
    
    while (num2.size() < num1.size()) {
        num2 = "0" + num2;// 通过添加前导0强行拉平size，从而规避索引分段考虑，一步到位
    }
    
    string result;
    int borrow = 0;
    
    for (int i = num1.size() - 1; i >= 0; i--) {
        int digit1 = num1[i] - '0';
        int digit2 = num2[i] - '0';
        
        digit1 -= borrow;
        
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        int diff = digit1 - digit2;
        result = char(diff + '0') + result;
    }
    
    while (result.size() > 1 && result[0] == '0') {
        result = result.substr(1);
    }
    
    if (result == "0") {
        return "0";
    }
    
    if (negative) {
        result = "-" + result;
    }
    
    return result;
}

int main() {
    int n = 0;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;
        
        if (a[0] == '+') a = a.substr(1);
        if (b[0] == '+') b = b.substr(1);
        
        if (a[0] == '-' && b[0] == '-') {
            a = a.substr(1);// .substr命令用于消解正负号
            b = b.substr(1);
            cout << kick(b, a) << endl;
        } else if (a[0] == '-' && b[0] != '-') {
            a = a.substr(1);
            cout << "-" << add(a, b) << endl;
        } else if (a[0] != '-' && b[0] == '-') {
            b = b.substr(1);
            cout << add(a, b) << endl;
        } else {
            cout << kick(a, b) << endl;
        }
    }
    
    return 0;
}