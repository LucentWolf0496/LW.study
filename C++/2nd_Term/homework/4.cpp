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