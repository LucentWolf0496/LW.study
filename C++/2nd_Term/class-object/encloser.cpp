// 封闭类————有成员对象的类叫“封闭(enclosing)类”。例如本代码中的类CCar
// 封闭类对象生成时，先执行所有对象成员的构造函数，然后才执行封闭类的构造函数。
// 对象成员的构造函数调用次序和对象成员在类中的说明次序一致，与它们在成员初始化列表中出现的次序无关。
// 当封闭类的对象消亡时，先执行封闭类的析构函数，然后再执行成员对象的析构函数。次序和构造函数的调用次序相反。
// 封闭类的对象，如果是用默认复制构造函数初始化的，那么它里面包含的成员对象，也会用复制构造函数初始化。

// 该程序展示了封闭类中成员对象的构造与析构的顺序————先构造的后析构！！
#include <iostream>
using namespace std;
class CTyre {
     public:
	CTyre() {  cout << "CTyre contructor" << endl; }
	~CTyre() { cout << "CTyre destructor" << endl; }
};
class CEngine {
     public:
	CEngine() { cout << "CEngine contructor" << endl; }
	~CEngine() { cout << "CEngine destructor" << endl; }
};
class CCar {
	private:
		CEngine engine;  
		CTyre tyre;
	public:
	CCar( )	{ cout << "CCar contructor" << endl; }
	~CCar() { cout << "CCar destructor" << endl; }
};
int main(){
	CCar car; 
	return 0;
}
// 该程序输出如下：
// CEngine contructor
// CTyre contructor
// CCar contructor
// CCar destructor
// CTyre destructor
// CEngine destructor