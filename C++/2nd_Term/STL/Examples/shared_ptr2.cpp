#include <iostream>
#include <memory>
using namespace std;
struct A{
 	~A() { cout << "~A" << endl; }
 };
int main()
{
	A * p = new A();
	shared_ptr<A> ptr(p);
	shared_ptr<A> ptr2;
	ptr2.reset(p);   //并不增加 ptr中对p的托管计数
	cout << "end" << endl;
	return 0;	
}
/*
输出：
end
~A
~A
之后程序崩溃，因 p被delete两次
*/