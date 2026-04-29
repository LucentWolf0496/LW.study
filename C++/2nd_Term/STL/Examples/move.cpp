#include <iostream>
#include <cstring>   // strlen, strcpy
using namespace std;

class String {
private:
    char* str;       // 指向动态分配的 C 风格字符串

public:
    // 默认构造：空字符串
    String() : str(new char[1]) {
        str[0] = '\0';
    }

    // 从 C 字符串构造
    String(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    // 拷贝构造函数
    String(const String& s) {
        cout << "copy constructor called" << endl;
        str = new char[strlen(s.str) + 1];
        strcpy(str, s.str);
    }

    // 拷贝赋值运算符
    String& operator=(const String& s) {
        cout << "copy operator= called" << endl;
        if (this != &s) {                // 防止自赋值
            delete[] str;
            str = new char[strlen(s.str) + 1];
            strcpy(str, s.str);
        }
        return *this;
    }

    // 移动构造函数
    String(String&& s) noexcept : str(s.str) {
        cout << "move constructor called" << endl;
        // 将源对象置为有效但空的“空字符串”状态
        s.str = new char[1];
        s.str[0] = '\0';
    }

    // 移动赋值运算符
    String& operator=(String&& s) noexcept {
        cout << "move operator= called" << endl;
        if (this != &s) {
            delete[] str;
            str = s.str;                 // 窃取资源
            // 让源对象指向一个新的空字符串，避免两次释放
            s.str = new char[1];
            s.str[0] = '\0';
        }
        return *this;
    }

    // 析构函数
    ~String() {
        delete[] str;
    }

    // 用于获取内部 C 字符串（只读）
    const char* c_str() const {
        return str;
    }
};

// 重载 << 运算符，方便输出
ostream& operator<<(ostream& os, const String& s) {
    os << s.c_str();
    return os;
}

// ------------------ 测试函数 ------------------
String createLocal() {
    String local("temporary");
    return local;      // 按理应调用移动构造，但编译器可能进行 RVO/NRVO 省略
}

int main() {
    cout << "===== 1. 默认构造 =====" << endl;
    String s1;                  // 空字符串
    cout << "s1 = \"" << s1 << "\"" << endl;

    cout << "\n===== 2. 从 const char* 构造 =====" << endl;
    String s2("Hello");
    cout << "s2 = \"" << s2 << "\"" << endl;

    cout << "\n===== 3. 拷贝构造 =====" << endl;
    String s3 = s2;             // 拷贝构造
    cout << "s3 = \"" << s3 << "\"" << endl;

    cout << "\n===== 4. 拷贝赋值 =====" << endl;
    String s4;
    s4 = s2;                    // 拷贝赋值
    cout << "s4 = \"" << s4 << "\"" << endl;

    cout << "\n===== 5. 移动构造 (显式 std::move) =====" << endl;
    String s5 = std::move(s2);  // 移动构造，s2 变为空字符串
    cout << "s5 = \"" << s5 << "\"" << endl;
    cout << "s2 after move = \"" << s2 << "\"" << endl;

    cout << "\n===== 6. 移动赋值 =====" << endl;
    String s6;
    s6 = std::move(s3);         // 移动赋值，s3 变为空
    cout << "s6 = \"" << s6 << "\"" << endl;
    cout << "s3 after move = \"" << s3 << "\"" << endl;

    cout << "\n===== 7. 函数返回局部对象 (可能发生 RVO) =====" << endl;
    String s7 = createLocal();   // 可能直接构造在 s7 上，不调用移动构造
    cout << "s7 = \"" << s7 << "\"" << endl;

    return 0;
}