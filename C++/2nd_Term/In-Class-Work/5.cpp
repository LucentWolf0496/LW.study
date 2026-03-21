// 本代码关键：
// 1.处理A以及A的指针！
//   +的重载左边是A，右边是A*，对应解引用的(*x)与后面两个指针相加，最终得到的是A对象，需要再重载变成指针
// 2.新奇的对运算符“->”的重载玩法：不要重载()，只有A()才能触发()的重载，而本题目前面没有A，所以要对->进行重载将对象A转为指针A*
//   而返回的this就是那个需要的指针A*
//   因为->运算符是针对指针的！！！指针才能调用->之后的内容使用对应函数
//   一定要记住->运算符是针对指针的
// 3.类的派生与继承：BC作为A的子类包括了A的所有内容
// 4.惊天大发现————*this 本质上就是对 this 指针的解引用！！！
//   成员函数本质上是在传递this这个指针，而左边的*是对指针的解引用运算符
//   根据字面意思，对指针*xxx解引用后得到的就是引用xxx（&xxx）————解引用的意思是说将指针解成引用
#include <iostream>
using namespace std;
class A{
    private:
        int num;
    public:
        A(){}
        A(int x):num(x){}
        void set(int x){num = x;}
        int get_value(){return num;}
        A* operator->() {return this;}// this是指针，而*this是常见的对this指针的解引用，返回普通的对象而不是指针
                                      // 但是只有指针才能接运算符->，所以这题需要重载将A换成A*
        friend A operator+(A x , A* y){// 这样达成连加运算，最终得到A，之后再重载变成A*
            A temp(x.num + y->get_value());
            A* temp0 = &temp;
            return temp;
        }
};

class B:public A{
    public:
        B(){}
        B(int x){A::set(x);}
};

class C:public A{
    public:
        C(){}
        C(int x){A::set(x);}
};

int main() {
    int t;
    cin >> t;
    while (t --){
        int aa, bb, cc;
        cin >> aa >> bb >> cc;
        A a(aa);
        B b(bb);
        C c(cc);
        A* x = &a;
        A* y = &b;
        A* z = &c;
        cout << (x->get_value() + y->get_value() + z->get_value()) << " ";// 这里就是三个正常的指针调用啦
        cout << ((*x) + y + z)->get_value() << endl;// *x是指针被解引用，为A。而y，z没经过处理，为A*
        // 内置 ->：只能用于指针。
        // 重载 ->：让类对象也能使用 ->，实际上是对编译器语法的扩展。
    }
    return 0;
}