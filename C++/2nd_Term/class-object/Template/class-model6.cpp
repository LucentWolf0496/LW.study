// 普通类从模板类派生
template <class T>
class A {   
	T v1;   
	int n;  
};

class B:public A<int> {   
	double v;	 
};

int main()  {  
	B obj1; 	
	return 0; 
}