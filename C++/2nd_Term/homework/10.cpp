#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
private:
    int **data;
    int row, col;
public:
    // 构造函数
    Array2(int r = 0, int c = 0) : row(r), col(c) {
        if (r == 0 || c == 0) {
            data = nullptr;
            row = col = 0;
        } else {
            data = new int*[r];
            for (int i = 0; i < r; ++i) {
                data[i] = new int[c];
            }
        }
    }
    // 析构函数
    ~Array2() {
        if (data) {
            for (int i = 0; i < row; ++i) {
                delete[] data[i];
            }
            delete[] data;
        }
    }
    // 拷贝构造函数
    Array2(const Array2 & other) : row(other.row), col(other.col) {
        if (other.data) {
            data = new int*[row];
            for (int i = 0; i < row; ++i) {
                data[i] = new int[col];
                for (int j = 0; j < col; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        } else {
            data = nullptr;
        }
    }
    // 赋值运算符
    Array2 & operator=(const Array2 & other) {
        if (this == &other) return *this;
        // 释放原有内存
        if (data) {
            for (int i = 0; i < row; ++i) {
                delete[] data[i];
            }
            delete[] data;
        }
        row = other.row;
        col = other.col;
        if (other.data) {
            data = new int*[row];
            for (int i = 0; i < row; ++i) {
                data[i] = new int[col];
                for (int j = 0; j < col; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        } else {
            data = nullptr;
        }
        return *this;
    }
    // 重载 []，返回行指针
    int *& operator[](int i) {
        return data[i];
    }
    // 重载 ()，访问元素
    int & operator()(int i, int j) {
        return data[i][j];
    }
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}