// 函数模板作为类模板的友元
#include <iostream>
#include <string>
using namespace std;

template <class T1,class T2>
class Pair{
private:
	T1 key;    //关键字
	T2 value;  //值
public:
	Pair(T1 k,T2 v):key(k),value(v) { };
	bool operator < ( const Pair<T1,T2> & p) const; 
    
	template <class T3,class T4>
	friend ostream & operator<< ( ostream & o, const Pair<T3,T4> & p);
};

template<class T1,class T2>
bool Pair<T1,T2>::operator < ( const Pair<T1,T2> & p) const{ //"小"的意思就是关键字小
	return key < p.key;
}

template <class T1,class T2>
ostream & operator<< (ostream & o,const Pair<T1,T2> & p){
	o << "(" << p.key << "," << p.value << ")" ;
	return o;
}

int main(){
	Pair<string,int> student("Tom",29);
	Pair<int,double> obj(12,3.14);
	cout << student << " " << obj;
	return 0;
}
// 输出：(Tom,29) (12,3.14)
// 任意从 template <class T1,class T2>
// ostream & operator<< (ostream & o,const Pair<T1,T2> & p)
// 生成的函数，都是任意Pair摸板类的友元