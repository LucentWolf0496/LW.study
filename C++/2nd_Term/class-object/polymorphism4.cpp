// 虚析构函数：调用基类指针删除时得以遵守先删除派生类再删除基类的规则
// 把基类的析构函数声明为virtual，派生类的析构函数可以virtual不进行声明
// 通过基类的指针删除派生类对象时，首先调用派生类的析构函数，然后调用基类的析构函数
// 然而，不允许以虚函数作为构造函数
#include <iostream>
using namespace std;

class son{
public:
	virtual ~son() {cout<<"bye from son"<<endl;};// 如果这里不设置成虚函数，就只会调用基类的析构函数
                                                 // 但设置虚函数就达成了多态，可以调用指向的grandson里面的析构函数
};
class grandson:public son{
public:
	~grandson(){cout<<"bye from grandson"<<endl;};
};
int main() {
	son *pson;
	pson= new grandson();
	delete pson;
	return 0;
}
