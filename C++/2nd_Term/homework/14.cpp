#include <iostream>
using namespace std;
class B { 
	private: 
		int nBVal; 
	public: 
		void Print() 
		{ cout << "nBVal="<< nBVal << endl; } 
		void Fun() 
		{cout << "B::Fun" << endl; } 
		B ( int n ) { nBVal = n;} 
};

class D: public B { 
	private: 
		int nDVal; 
	public: 
		void Print() { 
            B::Print();
            cout << "nDVal="<< nDVal << endl;
        } 
		void Fun() {cout << "D::Fun" << endl; } 
		D (int n):B(n * 3) { nDVal = n;} 
};

int main() { 
	B * pb; D * pd; 
	D d(4); d.Fun(); 
	pb = new B(2); pd = new D(8); 
	pb -> Fun(); pd->Fun(); 
	pb->Print (); pd->Print (); 
	pb = & d; pb->Fun(); // 复制了d，但是只能访问B类下面的内容，所以根据B类下面的Fun和Print函数输出
	pb->Print(); // d初始化dval为4的时候，bval变成12
	return 0;
}