// 阐明构造函数和析构函数的运行调用规律
#include <iostream>
using namespace std;

class Demo {
	int id;
public:	
	Demo(int i){
		id = i;
		cout << "id=" << id << " constructed" << endl;	 
	}
	~Demo(){
		cout << "id=" << id << " destructed" << endl;	 
	}
};

Demo d1(1);
void Func(){
	static Demo d2(2);
	Demo d3(3);
	cout << "func" << endl;
}
int main(){
	Demo d4(4);
	d4 = 6;// 临时变量，创建后就消除
	cout << "main" << endl;
	{    
        Demo d5(5); 	
    }
	Func();
	cout << "main ends" << endl;
	return 0;
}