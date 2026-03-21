// 本代码关键：
// 1.成员函数返回本类对象，记得return *this————当然，后置++的重载可以保存*this然后返回新的虚设值————然而，赋值重载必须返回*this
//   总之成员函数就是携带了可使用的this指针，如果没有其他返回要返回*this(this指针解引用之后的原对象)
// 2.与之对应的是，全局函数返回本类对象，应该先虚设一个对象然后填充
// 3.getValue函数int取引用就可以通过函数调用修改num值，属于是“越界”访问private变量的一种方式
// ****一件很重要的事情就是非void函数必须要有返回值————return一件事情————就看用什么填充：int或者是虚设的函数内临时变量****
#include <iostream>
using namespace std;

class A {
public:
    int num;
    A(){}
    A(int x){num = x;}
    A(const A& x){num = x.num;}
    friend ostream& operator<<(ostream& os , A x){
        os << x.num;
        return os;
    }
    int & getValue(){return num;}
    A & operator+=(A x){
        num += x.num;
        return *this;// 成员函数返回*this，因为必须要有一个return返回
    }
    A & operator-=(int x){
        num -= x;
        return *this;
    }
};

int main() {
	int t;
	cin >> t;
	while(t--) {
		int m , n , k;
		cin >> m >> n >> k;	
	    A a(m);
	    A b = a;
	    cout << b << endl;
	    cout << (a += b -= n) << endl;
	    cout << a.getValue() << endl;
	    a.getValue() = k;
	    cout << a << endl;
	} 
	return 0;
}