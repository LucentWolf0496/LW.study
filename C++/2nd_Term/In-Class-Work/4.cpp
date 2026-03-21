// 本代码关键：
// 正确理解复制构造函数Counter b4 = b2;！！！这个语句不是对运算符重载而是复制构造！！！
// 运算符重载应该是：
// Counter b4;
// b4 = b2;
// 不要瞎猫碰上死耗子，要真正了解函数的运行逻辑，计数增加的逻辑！！
#include <iostream>
using namespace std;

class Counter {
private:
	static int nGlobalNumber;
	int nLocalNumber;
public:
    Counter() : nLocalNumber(1) { nGlobalNumber++; }
    Counter(int n) : nLocalNumber(n) { nGlobalNumber++; }
    Counter(const Counter& other) : nLocalNumber(other.nLocalNumber) { nGlobalNumber++; }
    // 这里不能写成=运算符的重载，而是复制构造函数
void add(int n) { nLocalNumber += n; }
void PrintLocalNumber(){cout << nLocalNumber << endl;}
static void PrintGlobalNumber() {cout << nGlobalNumber << endl;}
};
int Counter::nGlobalNumber = 0;

int main()
{
	Counter::PrintGlobalNumber();
	Counter b1, b2;
	Counter::PrintGlobalNumber();
	b1.PrintLocalNumber();
	b2.add(10);
	b2.PrintLocalNumber();
	Counter* b3 = new Counter(7);
	b3->PrintLocalNumber();
	Counter b4 = b2;
	b4.PrintLocalNumber();
	Counter::PrintGlobalNumber();
	if (b3 != NULL){
		delete b3;
		b3 = NULL;
	}
	Counter::PrintGlobalNumber();
	return 0;
}