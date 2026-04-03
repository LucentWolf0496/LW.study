// 类模板与友员函数
// 函数、类、类的成员函数作为类模板的友元
// 函数模板作为类模板的友元
// 函数模板作为类的友元
// 类模板作为类模板的友元

// 函数、类、类的成员函数作为类模板的友元
void Func1() {  }

class A {  };

class B{
public:
   void Func() { } 	  
};

template <class T>
class Tmpl {
   friend void Func1();
   friend class A;
   friend void B::Func();
}; //任何从Tmp1实例化来的类，都有以上三个友元