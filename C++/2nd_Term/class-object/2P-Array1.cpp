#include <iostream>
#include <cstdlib>
using namespace std;

class Array{
    private:
        int *list;
        int size;
    public:
        Array():list(NULL) , size(0){  }
        Array(int x):size(x){ list = new int[x]; }
        ~Array(){ delete[] list; }
        int & operator[](int x){ return list[x]; }
        Array & operator=(const Array & x){
            if (this == &x) return *this;// 自赋值检查
            // this —— 指向当前对象的指针
            // *this —— 当前对象本身的引用
            // x —— 参数引用的对象
            // &x —— 源对象的地址
            // this == &x：比较地址是否相同判断是不是自我赋值
            if (list) delete[] list;
            list = new int[x.size];
            memcpy(list , x.list , sizeof(int) * x.size);// 对int要用memcpy，对char就可用strcpy
            size = x.size;
            return *this;
        }
        Array(const Array & x){
            if (x.list){
                list = new int[x.size];
                memcpy(list , x.list , sizeof(int) * x.size);
                size = x.size;
            }
            else{
                list = NULL;
                size = 0;
            }
        }
        friend Array operator+(const Array & x , const Array & y);
};

Array operator+(const Array & x , const Array & y){
    if (!x.list && !y.list) return Array(0);
    else if (x.list && !y.list) return Array(x);
    else if (!x.list && y.list) return Array(y);
    else{
        Array result(x.size + y.size);
        memcpy(result.list, x.list, sizeof(int) * x.size);
        memcpy(result.list + x.size, y.list, sizeof(int) * y.size);
        return result;
    }
}

int main(){
    Array a(5);
    a[2] = 1;
    Array b(a);
    cout << a[2] << " " << b[2] << endl;
    Array c(4);
    c[2] = 2;
    c[3] = 0;
    b = c;
    cout << b[2] << " " << b[3] << endl;
    Array zero(0);
    Array d = c + zero;
    Array e = d + d;
    cout << d[2] << " " << e[6] << endl;;
}