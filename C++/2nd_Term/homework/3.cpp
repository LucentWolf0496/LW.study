// 类的 static int 变量是类级别的共享变量
// 所有对象共用一份存储，常用于记录与类整体相关的状态信息。
#include <iostream>
using namespace std;

class Apple {
public:// 记得写上public&private
    static int nTotalNumber;
//static int 变量在 C++ 中通常指的是类的静态成员变量。它的含义和特点如下：
//属于类本身，而非某个对象
//静态成员变量不是被每个对象单独拥有的，而是由整个类共享的一份数据。
//无论创建了多少个对象，该变量在内存中只有一份拷贝。
//所有对象访问的都是同一个静态变量。
    Apple() { nTotalNumber++; }
    ~Apple() { nTotalNumber--; }
    static void PrintTotal() {
		cout << nTotalNumber << endl; 
	}
};

int Apple::nTotalNumber = 0;
// 访问方式————通过类名::变量名访问（推荐）：
// Apple::nTotalNumber = 10;

// 也可以通过对象访问（编译器会将其转换为类名访问）：
// Apple a;
// a.nTotalNumber = 10;   // 实际上修改的是同一个变量

Apple Fun(const Apple & a) {
	a.PrintTotal();
	return a;
}

int main(){
	Apple * p = new Apple[4];
	Fun(p[2]);
	Apple p1,p2;
	Apple::PrintTotal ();
	delete [] p;
	p1.PrintTotal ();
	return 0;
}