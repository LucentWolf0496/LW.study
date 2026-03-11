#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>

using namespace std;

class Calculator {
private:
    string expr;
    size_t pos;
    
    // 跳过空格
    void skipSpaces() {
        while (pos < expr.size() && isspace(expr[pos])) {
            pos++;
        }
    }
    
    // 获取下一个字符，不移动指针
    char peek() {
        skipSpaces();
        if (pos < expr.size()) {
            return expr[pos];
        }
        return '\0';
    }
    
    // 获取下一个字符并移动指针
    char get() {
        skipSpaces();
        if (pos < expr.size()) {
            return expr[pos++];
        }
        return '\0';
    }
    
    // 解析数字（包括处理一元正负号）
    int parseNumber() {
        skipSpaces();
        
        // 处理一元正负号
        int sign = 1;
        while (peek() == '+' || peek() == '-') {
            if (get() == '-') {
                sign = -sign;
            }
        }
        
        // 如果是括号，解析括号表达式
        if (peek() == '(') {
            get(); // 跳过 '('
            int result = parseExpression();
            if (peek() == ')') {
                get(); // 跳过 ')'
            }
            return sign * result;
        }
        
        // 解析数字
        int num = 0;
        while (isdigit(peek())) {
            num = num * 10 + (get() - '0');
        }
        
        return sign * num;
    }
    
    // 解析项（处理 * 和 /）
    int parseTerm() {
        int result = parseNumber();
        
        while (true) {
            skipSpaces();
            char op = peek();
            if (op == '*' || op == '/') {
                get(); // 跳过运算符
                int right = parseNumber();
                if (op == '*') {
                    result *= right;
                } else {
                    result /= right; // 整数除法
                }
            } else {
                break;
            }
        }
        
        return result;
    }
    
    // 解析表达式（处理 + 和 -）
    int parseExpression() {
        int result = parseTerm();
        
        while (true) {
            skipSpaces();
            char op = peek();
            if (op == '+' || op == '-') {
                get(); // 跳过运算符
                int right = parseTerm();
                if (op == '+') {
                    result += right;
                } else {
                    result -= right;
                }
            } else {
                break;
            }
        }
        
        return result;
    }
    
public:
    Calculator(const string& s) : expr(s), pos(0) {}
    
    int evaluate() {
        return parseExpression();
    }
};

int main() {
    string line;
    
    // 逐行读取输入
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        Calculator calc(line);
        int result = calc.evaluate();
        cout << result << endl;
    }
    
    return 0;
}