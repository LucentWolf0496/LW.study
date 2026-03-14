#include <iostream>
using namespace std;
class A {
public:
	int val;

	A(int x){
        val = x;
    }
    A(){
        val = 123;
    }
    A& GetObj(){
        return *this;
    }
    // 当调用 a.GetObj() 时，它返回对象 a 自身的引用，相当于将 a 的别名暴露给外界。
    // 随后执行 = m，即对返回的引用进行赋值。由于该引用绑定到 a，所以赋值操作实际作用于 a 本身，相当于 a = m。
    // 这种写法的意义在于，通过成员函数返回引用，可以允许将函数调用放在赋值运算符的左侧，从而修改原对象。
    // 如果 GetObj() 返回的是值而非引用，则 a.GetObj() 会生成一个临时副本，对其赋值将毫无意义。
};
int main()
{
	int m,n;
	A a;
    A b = 5;
    A c = A(3);
    A d = A();
    cout << b.val << c.val << d.val;
	cout << a.val << endl;
	while(cin >> m >> n) {
		a.GetObj() = m;
		cout << a.val << endl;
		a.GetObj() = A(n);
		cout << a.val<< endl;
	}
	return 0;
}