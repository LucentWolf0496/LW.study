// 自增运算符++、自减运算符--有前置/后置之分
// 前置运算符作为一元运算符重载
// 重载为成员函数：T & operator++(); T & operator--();
// 重载为全局函数：T1 & operator++(T2); T1 & operator—(T2);
// 后置运算符作为二元运算符重载，多写一个没用的参数：
// 重载为成员函数：T operator++(int); T operator--(int);
// 重载为全局函数：T1 operator++(T2,int ); T1 operator—( T2,int);
#include <iostream>
using namespace std;

class CDemo {
    private :
	    int n;
    public:
	    CDemo(int i=0):n(i) { }
	    CDemo & operator++();      //用于前置形式
	    CDemo operator++( int );   //用于后置形式
        operator int ( ) { return n; }
        CDemo & operator--();
        CDemo operator--(int);    
};

CDemo & CDemo::operator++(){ //前置 ++
	n ++;
	return * this;
}  // ++s即为: s.operator++();

CDemo CDemo::operator++( int k ){ //后置 ++
	CDemo tmp(*this); //记录修改前的对象
	n ++;
	return tmp; //返回修改前的对象
} // s++即为: s.operator++(0);

CDemo & CDemo::operator--() {//前置--
 	n--;
	return *this; 	  
} //--s即为: operator--(s);

CDemo CDemo::operator--(int) {//后置--
 	CDemo tmp(*this);
	n --;
	return tmp;  
} //s--即为: operator--(s, 0);

int main(){
	CDemo d(5);
	cout << (d++ ) << ",";  //等价于 d.operator++(0);
	cout << d << ",";
	cout << (++d) << ",";   //等价于 d.operator++();
	cout << d << endl;
	cout << (d-- ) << ",";  //等价于 operator--(d,0);
	cout << d << ",";
	cout << (--d) << ",";   //等价于 operator--(d);
	cout << d << endl;
	return 0;
}
// 输出1：5 6 7 7
// 输出2：7 6 5 5 