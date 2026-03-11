// 静态成员：在定义前面加了static关键字的成员。
// 普通成员变量每个对象有各自的一份，而静态成员变量一共就一份，为所有对象共享。
// sizeof 运算符不会计算静态成员变量。不算大小，静态成员相当于“这个类中的全局变量”
// 静态成员变量一共就一份，为所有对象共享。
// 静态成员函数并不具体作用于某个对象。

// 结论：因此静态成员不需要通过对象就能访问。
// 记得要初始化静态成员
// 在静态成员函数中，不能访问非静态成员变量，也不能调用非静态成员函数。

// 静态成员访问方式：不需要通过对象就能访问。
// 1) 类名::成员名————CRectangle::PrintTotal(); 
// 2) 对象名.成员名————CRectangle r; r.PrintTotal();
// 3) 指针->成员名————CRectangle * p = &r;   p->PrintTotal();
// 4) 引用.成员名————CRectangle & ref = r;  int n = ref.nTotalNumber; 

// 关于静态函数的作用、取参数的范围讨论：
// 静态成员函数中不能使用 this 指针！
// 因为静态成员函数并不具体作用与某个对象!
// 因此，静态成员函数的真实的参数的个数，就是程序中写出的参数个数！
// 类的非静态成员函数，真实的参数比所写的参数多1————比静态函数更多出来一个*this指针

// 程序示例：
#include <iostream>
using namespace std;

class CRectangle{
	private:
    	int w, h;
	    static int nTotalArea;
    	static int nTotalNumber;
	public:
	    CRectangle(int w_,int h_);
        CRectangle(CRectangle & r );// 补写复制构造函数
       	~CRectangle();
	    static void PrintTotal();       
};

CRectangle::CRectangle(int w_,int h_){
    w = w_;
    h = h_;
    nTotalNumber ++;// 存在缺陷？？复制构造函数没有写出来，是缺省的，就不会让矩形数目+1
                    // 应该补写复制构造函数使其增加对应static int
    nTotalArea += w * h;    
}

CRectangle :: CRectangle(CRectangle & r ){// 补写复制构造函数
  	w = r.w;   h = r.h;
	nTotalNumber ++;
	nTotalArea += w * h;
}

CRectangle::~CRectangle(){
    nTotalNumber --;// 析构函数正常工作，不受到影响
    nTotalArea -= w * h;
}

void CRectangle::PrintTotal(){
    cout << nTotalNumber << "," <<   nTotalArea << endl; 
}

int CRectangle::nTotalNumber = 0;
int CRectangle::nTotalArea = 0;
//必须在定义类的文件中对静态成员变量进行一次说明或初始化。否则编译能通过，链接不能通过。

int main(){
	CRectangle r1(3,3), r2(2,2);
	//cout << CRectangle::nTotalNumber; // Wrong , 私有
	CRectangle::PrintTotal();
	r1.PrintTotal();
	return 0;
}