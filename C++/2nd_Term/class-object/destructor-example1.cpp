#include <iostream>
using namespace std;

class CMyclass {
	public:
	CMyclass() {};
	CMyclass( CMyclass & c){ cout << "copy constructor" << endl; }
	~CMyclass() { cout << "destructor" << endl; }
};

void fun(CMyclass obj_ ) {
	cout << "fun" << endl;
}

CMyclass c;
CMyclass Test( ) {
	cout << "test" << endl;
	return c;
}

int main(){
	CMyclass c1;
	fun( c1);
	Test();
	return 0;
}
// 输出：
// copy constructor
// fun
// destructor
// test
// copy constructor
// destructor
// destructor
// destructor