#include <iostream>
#include <cmath>
using namespace std;

// 函数声明
bool isPrime(int);

int main() {
    int num;
    
    cout << "质数判断程序" << endl;
    cout << "------------" << endl;
    cout << "请输入一个正整数: ";
    
    cin >> num;
    
    if (cin.fail() || num < 0) {
        cout << "输入无效，请输入一个正整数！" << endl;
        return 1;
    }
    
    if (isPrime(num)) {
        cout << num << " 是质数" << endl;
    } else {
        cout << num << " 不是质数" << endl;
    }
    
    return 0;
}

// 判断质数的函数
bool isPrime(int nf) {
    // 小于等于1的数不是质数
    if (nf <= 1) {
        return false;
    }
    
    // 2和3是质数
    if (nf <= 3) {
        return true;
    }
    
    // 能被2或3整除的数不是质数
    if (nf % 2 == 0 || nf % 3 == 0) {
        return false;
    }
    
    // 检查6k±1形式的因子
    // 形如6k+2，3，4都是合数，故检查6k+1/6k+5，6k+5就是6k-1
    // 条件是pow(i , 2)小于等于n，故检查只小于等于根号n的因数，ok
    for (int i = 5; i * i <= nf; i += 6) {
        if (nf % i == 0 || nf % (i + 2) == 0) {
            return false;
        }
    }
    
    return true;
}