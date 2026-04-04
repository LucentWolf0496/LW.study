// 类模板从模板类派生
template <class T1,class T2>  
class A {   
	T1 v1; T2 v2;	 
};

template <class T>
class B:public A<int,double> {   
	T v;	  
};

int main()  {	  
	B<char> obj1;  //自动生成两个模板类：A<int,double> 和 B<char>
  	return 0; 
}