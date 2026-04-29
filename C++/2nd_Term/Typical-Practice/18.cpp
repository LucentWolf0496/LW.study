#include<iostream>
using namespace std;

template<class T>
class Accumulator
{
public:
	T sum;
	Accumulator() {sum = T();}
	auto getAccumulator() {
		return [this](T v) { sum += v; };
// 返回的lambda就“内嵌”了对应对象的sum，可以用于累加
/*this 捕获：
lambda 的定义 [this](T v){ sum += v; } 将当前对象的 this 指针（例如 A 的地址）存储到 lambda 内部。
lambda 闭包中相当于有一个隐藏的指针成员，指向原始的 Accumulator 对象。*/

	}
	void printval() {
		cout << sum << endl;
	}
};

int main()
{
	Accumulator<int> A;
	int n; cin >> n;
	auto funcA = A.getAccumulator();// 返回的lambda就“内嵌”了对应对象的sum，可以用于累加
	for (int i = 0; i < n; i++) {
		int v; cin >> v;
		funcA(v);
	}
	A.printval();
	
	Accumulator<string> B;
	cin >> n;
	auto funcB = B.getAccumulator();// 返回的lambda就“内嵌”了对应对象的sum，可以用于累加
	for (int i = 0; i < n; i++) {
		string v; cin >> v;
		funcB(v);
	}
	B.printval();
	return 0;
}