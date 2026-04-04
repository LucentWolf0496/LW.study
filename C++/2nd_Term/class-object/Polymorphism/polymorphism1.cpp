// 1234567890-=]'/.,mnbvcxzaqwertyuiop[;lkjhgfds
// 1.虚函数virtual：
// 在类的定义中，前面有 virtual 关键字的成员函数就是虚函数。
// virtual 关键字只用在类定义里的函数声明中，写函数体时不用。
// 2.多态的指针表现形式：
// 派生类的指针可以赋给基类指针。 
// 通过基类指针调用基类和派生类中的同名同参虚函数时:
// （1）若该指针指向一个基类的对象，那么被调用是基类的虚函数。
// （2）若该指针指向一个派生类的对象，那么被调用的是派生类的虚函数。
// 3.多态中的override标识符号：
// override 的作用：显式声明：告诉编译器“这个函数是要覆盖基类中的虚函数”。
// 帮助编译器检查：如果基类中没有匹配的虚函数（例如函数名、参数、常量性不匹配），编译器会报错，从而避免因书写错误而意外地创建新函数。
// C++11 同时引入了 final 关键字，表示禁止进一步重写。override 和 final 可以同时使用：

// 4.多态的引用表现形式：与指针类比学习
// 派生类的对象可以赋给基类引用
// 通过基类引用调用基类和派生类中的同名同参虚函数时:
// （1）若该引用引用的是一个基类的对象，那么被调用是基类的虚函数；
// （2）若该引用引用的是一个派生类的对象，那么被调用的是派生类的虚函数。

#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() { cout << "Animal speaks" << endl;}//虚函数
};

class Dog : public Animal {
public:
    void speak() override { cout << "Dog barks" << endl;}// 重写虚函数
    Dog* operator->(){ return this; }
};

class Cat : public Animal {
public:
    void speak() override { cout << "Cat meows" << endl;}
};

int main() {
    // 指针version
    Dog 🐺;
    Animal 🦁;
    Animal* 🐸 = &🦁;// 指针要通过地址赋值（基本运算细节）
    Animal* 🐱 = new Cat();// 或者直接new出来指针
    🐸->speak();
    🐺->speak();// 被重载的->运算符
    🐱->speak();
    delete 🐸; delete 🐱;// 🐺是被重载的非指针对象，所以不用删除

    cout << endl;

    // 引用version
    Animal animal;
    Dog dog;
    Cat cat;
    // 基类引用
    Animal& ref1 = animal;   // 绑定到基类对象
    Animal& ref2 = dog;      // 绑定到派生类对象
    Animal& ref3 = cat;      // 绑定到派生类对象
    ref1.speak();   // 输出：Animal speaks————引用就直接.来访问函数，指针需要->
    ref2.speak();   // 输出：Dog barks
    ref3.speak();   // 输出：Cat meows

    return 0;
}