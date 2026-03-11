// 面向对象的程序设计方法，能够较好解决上述问题。
// 面向对象的程序 = 类 + 类 + …+ 类 
// 设计程序的过程，就是设计类的过程。
// 面向对象的程序设计具有“抽象”，“封装”“继承”“多态”四个基本特点。
// 实际上，“类”看上去就像“带函数的结构”。
// 在 C++ 中，struct 和 class 几乎相同，唯一的区别是默认访问权限：
// 使用 class 定义时，成员默认是 private。使用 struct 定义时，成员默认是 public。
// 但实际编程中，struct 通常用于仅包含数据的简单结构，而 class 用于具有复杂逻辑的封装体。
// 访问控制 (private & public) 是 C++ 实现封装的关键工具，它帮助我们构建更健壮、易维护的程序。
#include <iostream>
using namespace std;

class Clock {
private:               // 私有成员：外界不能直接访问
    int hour;
    int minute;
    int second;

public:                // 公有接口：外界通过它们来操作钟表
    void setTime(int h, int m, int s) {
        // 可以添加合法性检查，保护数据
        if (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60) {
            hour = h;
            minute = m;
            second = s;
        } else {
            cout << "无效时间！" << endl;
        }
    }

    void showTime() {
        cout << hour << ":" << minute << ":" << second << endl;
    }
};

int main() {
    Clock myClock;
    // myClock.hour = 10;   // 错误！hour 是 private，不能直接访问
    myClock.setTime(10, 30, 0);   // 通过公有函数设置时间
    myClock.showTime();           // 通过公有函数显示时间
    return 0;
}