// 判断点是不是在正方形里，审题！！！
#include <iostream>
using namespace std;

int main() {
    float x, y;
    char comma;
    
    // 读取x值、逗号和y值
    // 审题！！！注意题目输入格式
    // 让加逗号就加上逗号！！！！！
    cin >> x >> comma >> y;
    
    // 检查点是否在正方形内（包括边界）
    if (x >= -1.0 && x <= 1.0 && y >= -1.0 && y <= 1.0) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    
    return 0;
}