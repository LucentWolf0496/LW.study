// 通过类，可以定义变量。类定义出来的变量，也称为类的实例，就是我们所说的“对象” 。
// C++中，类的名字就是用户自定义的类型的名字。可以象使用基本类型那样来使用它。CRectangle 就是一种用户自定义的类型。
// ！！！本质上，class就是更高级的struct，带上了函数玩！！！比如说是类似结构体struct————使用.来进行处理
// 和结构变量一样，对象所占用的内存空间的大小，等于所有成员变量的大小之和。
// 对于上面的CRectangle类，sizeof(CRectangle) = 8 ———— 一个int大小为4，两个大小为8，而成员函数不占对象内存
// 每个对象各有自己的存储空间。一个对象的某个成员变量被改变了，不会影响到另一个对象。
// 对象间不能比大小，除非经过了重载
// 传引用比传值更高效！！免去了拷贝的过程，直接传递地址

#include <iostream>
using namespace std;

class CRectangle
{
public:
    int w, h;
    int Area() {
        return w * h;
    }
    int Perimeter() {
        return 2 * (w + h);
    }
    void Init( int w_, int h_ ) {// 初始化函数
        w = w_; h = h_;
    }
};  // 必须有分号

int main() {
    int w, h;
    CRectangle r;// r是一个对象
    cin >> w >> h;
    r.Init( w, h );// r.这种写法就说明了处理的是CRectangle类下的对象r，引用的是r中的函数
    cout << r.Area() << endl << r.Perimeter();
    return 0;
}