// 类模板与派生————类模板从类模板派生，类模板从模板类派生，类模板从普通类派生，普通类从模板类派生
// 包含在代码示例3-6之中

// 类模板从类模板派生
template <class T1,class T2>
class A  {   
	T1 v1; T2 v2;	  
};

template <class T1,class T2>
class B:public A<T2,T1>  {   
    T1 v3; T2 v4;	  
};

template <class T>
class C:public B<T,T>  {   
	T v5;		
};

int main()	{
 	B<int,double> obj1; 
	C<int> obj2; 	
 	return 0;
}