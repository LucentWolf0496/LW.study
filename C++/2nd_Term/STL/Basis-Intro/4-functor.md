functor（仿函数），也就是函数对象:
形式上是对象但实际上可作为函数使用，作为函数使用的时候又创建了对象
函数对象————是个对象，但是用起来看上去像函数调用，实际上也执行了函数调用。
基于函数指针的进步：函数对象通常可以被编译器更积极地内联，而函数指针可能阻碍优化。

函数对象的应用：以STL中的一个模板accumulate为例子：
template<class InIt, class T, class Pred> 
T accumulate(InIt first, InIt last, T val, Pred pr); 
模板之中：
pr 就是个函数对象————对[first,last)中的每个迭代器 I, 执行 val = pr(val,* I) ,返回最终的val。
另外，pr也可以是个函数。

greater 的应用：
list 有两个sort函数，前面例子中看到的是不带参数的sort函数，它将list中的元素按 < 规定的比较方法 升序排列。
list还有另一个sort函数：
    template <class T2>
    void sort(T2 op); 
    可以用 op来比较大小，即 op(x,y) 为true则认为x应该排在前面
————所以不只是greater，还可以自定义更多用于sort比较的大小判断规律！！
————定义出函数对象再调用即可！！详见【functor3.cpp】中代码示例

用sort进行排序：
用自定义的排序规则，对任何类型T的数组排序
sort(数组名+n1，数组名+n2,排序规则结构名());
排序规则结构的定义方式： 注意传递引用要加const，符合模板的传递变量形式！！
struct 结构名 {
    bool operator()( const T & a1,const T & a2) {
        //若a1应该在a2前面，则返回true。
        //否则返回false。 
    }
};

引入函数对象后，STL中的“大”，“小”关系————此时需要重载运算符：
关联容器和STL中许多算法，都是可以自定义比较器的。在自定义了比较器op的情况下，以下三种说法是等价的：
1) x小于y
2) op(x,y)返回值为true
3) y大于x