// 类模板从普通类派生
class A {   
	int v1;  
};

template <class T>
class B:public A {   //所有从B实例化得到的类，都以A为基类 
	T v; 
};

int main() { 
	B<char> obj1;  
	return 0; 
}