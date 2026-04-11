// 基础练习：函数重载、静态数组初始化（题目给指针另说————list = new T[x]）、函数指针传递
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
template<class T , int x>
class A{
public:

T list[x];// 静态数组，无需手动管理，不要用指针！
A(T b[]) {
    for (int i = 0; i < x; ++i) {
        list[i] = b[i];
    }
}

// 重载两个sum函数
int sum(int m , int n , int (*f)(T)){// 注意函数指针的传递表述，前面是返回类型，函数名字用指针+括号，最后是参数类型
    int result = 0;
    for (int i = m ; i <= n ; i ++){
        result += f(list[i]);
    }
    return result;
}

string sum(int m , int n , string (*f)(T)){
    string result = "";
    for (int i = m ; i <= n ; i ++){
        result += f(list[i]);
    }
    return result;
}
};

string int2string(int x) { return to_string(x); }
int int2squareint(int x) { return x * x; }

int string2int(string str) {
	int res = 0;
	for (string::iterator iter = str.begin(); iter != str.end(); ++iter)
		res += *iter;
	return res;
}
string string2longerstring(string str) { return str + str; }

int main() {

	int t;
	cin >> t;
	while (t--) {
		int b1[10];
		for (int i = 0; i < 10; ++i)

			cin >> b1[i];
		A<int, 10> a1 = b1;
		cout << a1.sum(2, 6, int2squareint) << endl;
		cout << a1.sum(2, 6, int2string) << endl;

		string b2[4];
		for (int i = 0; i < 4; ++i)
			cin >> b2[i];

		A<string, 4> a2 = b2;
		cout << a2.sum(0, 3, string2int) << endl;
		cout << a2.sum(0, 3, string2longerstring) << endl;
	}
	return 0;
}