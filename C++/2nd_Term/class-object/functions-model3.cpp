// 函数模板示例：Map————函数也能传进模板?!
#include <iostream>
using namespace std;
template<class T,class Pred>
void Map(T s, T e, T x, Pred op)
// 当你调用 Map(a, a+5, b, Square) 时，Square 是一个函数名，它会被隐式转换为函数指针 int (*)(int)。
// 编译器推导 Pred 的类型为 int (*)(int)（函数指针类型），然后 op 就是一个函数指针，可以通过 op(*s) 调用。
{	
	for(; s != e; ++s,++x) {
		*x = op(*s);
	}
}

int Cube(int x) {	return x * x * x; }
double Square(double x) {	return x * x; }
int a[5] = {1,2,3,4,5}, b[5];
double d[5] = { 1.1,2.1,3.1,4.1,5.1} , c[5];
int main() {
	Map(a,a+5,b,Square);
	for(int i = 0;i < 5; ++i) cout << b[i] << ",";
	cout << endl;
	
	Map(a,a+5,b,Cube);
	for(int i = 0;i < 5; ++i) cout << b[i] << ",";
	cout << endl;
	
	Map(d,d+5,c,Square);
	for(int i = 0;i < 5; ++i) cout << c[i] << ",";
	cout << endl;
	return 0;   
}