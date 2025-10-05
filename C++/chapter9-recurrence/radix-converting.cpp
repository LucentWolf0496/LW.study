// 位数过多int甚至double都存不下？
// 就用直接的，单位次递归来转进制！！！
// 从高位向低位处理进位，避免非整十数的次方在低位产生大量数码导致无法正确进位！！！
// 先进位转10，后由10转目标进制（套路题）
// 进位转10进制通过for循环，迭代完成
// 10进制转目标进制通过大数除法求余数，迭代完成

// 迭代综合理解练习题目！！

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
// 从高位向低位进行处理，高位进位完再管下一低位
vector<int> convertToDecimal(const string& s, int a) {
    vector<int> decimal;
    if (s.empty()) return decimal;
    
    // 初始化：第一个数字
    decimal.push_back(f(s[0]));// 以最高位为基础
    
    for (int i = 1; i < s.length(); i++) {// 从次高位开始递减循环
        int current = f(s[i]);
        
        // 乘以基数a，对n位乘以n - 1个a从而达成进制转化
        // 打包乘以之前所有的数，但新加入的数不乘以a，确保仅n - 1次乘法
        // 就算已经进位变化成十进制数，但是乘法依然生效，因为揉回去还是a进制，只是在十进制“投射展开”
        // 因此就算进位的位置再乘以a，也都是符合a进制算法规律的 ！！
        int carry = 0;
        for (int j = 0; j < decimal.size(); j++) {// 进位器，仔细理解
            int temp = decimal[j] * a + carry;// 不一次将某位的a乘完，一步一步乘以a
                                              // 从而最终实现进制转换所需乘以的所有a
            decimal[j] = temp % 10;
            carry = temp / 10;// 一步一步乘以a更方便逐步进位处理！！
        }
        
        // 处理剩余的进位
        while (carry > 0) {
            decimal.push_back(carry % 10);// 注意：十进制数是逆序的，左低位右高位
            carry /= 10;
        }
        
        // 加上当前位，当前位不乘以a
        carry = current;
        for (int j = 0; j < decimal.size() && carry > 0; j++) {// carry > 0 作为优化，提前终止循环
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
    vector<int> quotient;// 学习利用强大的vector数组存储以防溢出
    
    // 当decimal不为0时继续转换
    while (!decimal.empty()) {
        // 模拟除法：decimal除以b
        int remainder = 0;
        quotient.clear();
        
        // 从高位到低位进行除法
        for (int i = decimal.size() - 1; i >= 0; i--) {
            int current = remainder * 10 + decimal[i];
            if (!quotient.empty() || current >= b) {
                quotient.push_back(current / b);
            }
            remainder = current % b;
        }
        
        // 余数就是当前位的值
        result.push_back(f1(remainder));// 注意转成字符，使用f1函数
        
        // 商作为新的被除数，循环求出b进制的从低位到高位数值
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
    cin.ignore();// 输入流经典处理，ignore命令忽略换行符

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
        vector<int> decimal = convertToDecimal(s, a);// 多用子函数使代码模块化，便于维护与理解！！
        
        // 转换为目标进制
        string result = convertFromDecimal(decimal, b);// 多用子函数使代码模块化，便于维护与理解！！
        
        cout << result << endl;
    }
    return 0;
}