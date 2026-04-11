// 对于cout的指针模式加工处理，研究输出相关的指针
#include <iostream>
#include <list>
#include <string>
using namespace std;

template <class T1,class T2>
void Copy(T1 s,T1 e, T2 x){
	for(; s != e; ++s,++x)// s在自增而++x被重载后就是个空操作，靠重载=来持续将内容*s输送给cout来输出
		*x = *s;
}
// 调用链分析
/*
以 Copy(lst.begin(), lst.end(), output); 为例：
output 是 myostream_iteraotr<int> 对象，构造时传入 cout 和 ","。
在 Copy 的循环体中，*x = *s 这一句到底发生了什么？
按照运算符优先级和重载规则：
先执行 *x：调用 x.operator*()，返回 *this（即 x 本身）。
然后执行赋值：(x) = *s，即调用 x.operator=(*s)。
所以 *x = *s 等价于 x.operator=(*s)。
operator=(*s) 被调用后，执行：
os << val << cut;   // val = *s 的值，例如 5,21,14,2,3
因为 os 就是 cout，所以就会向屏幕输出 5,21,14,2,3,。
*/

// 总结：
/*
数据从源（list 或数组）来，通过 Copy 函数逐个取出。
*x = *s 触发输出：因为 operator= 被重载为向 cout 发送数据。
++x 只是形式，满足迭代器语法，不改变任何状态。
最终所有输出都汇集到构造时传入的 cout。
*/
 
template<class T>
class myostream_iteraotr{
private:
    ostream & os;// 正是由于 os 的类型是 ostream &，且被初始化为 cout 的引用，所以 os 就“充当”了 cout 的角色。
    string cut;
public:
	/*
	operator*() 返回 *this（即迭代器自身）
	operator++() 也返回 *this（空操作，但满足迭代器语法要求）
	!!!!!!!operator=(const T& val) 才是真正做输出的地方：它把 val 和分隔符送到 os 流中。!!!!!!!
	*/
    myostream_iteraotr(ostream& o, const string& x) : os(o), cut(x) {}
    myostream_iteraotr& operator*() { return *this; }
    myostream_iteraotr& operator++() { return *this; }
    myostream_iteraotr& operator++(int) { return *this; }
    void operator=(const T& val) {
        os << val << cut;
    }
};

int main(){
    const int SIZE = 5;
	int a[SIZE] = {5,21,14,2,3};
	double b[SIZE] = { 1.4, 5.56,3.2,98.3,3.3};
	list<int> lst(a,a+SIZE);
	myostream_iteraotr<int> output(cout,",");
	Copy( lst.begin(),lst.end(),output); 
	cout << endl;
	myostream_iteraotr<double> output2(cout,"--");
	Copy(b,b+SIZE,output2);
	return 0;
}