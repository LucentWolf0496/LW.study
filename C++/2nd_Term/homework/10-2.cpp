#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
    private:
        int **table;
        int row;
        int col;
    public:
        Array2(int x = 0 , int y = 0):row(x) , col(y){
            if (x == 0 && y == 0) table = NULL;
            table = new int*[row];
            for (int i = 0 ; i < x ; i ++) table[i] = new int[col];
        }
        ~Array2(){
            for (int i = 0 ; i < row ; i ++) delete[] table[i];
            delete[] table;
        }
        int *& operator[](int i) {
            return table[i];
        }
        int & operator()(int i, int j) {
            return table[i][j];
        }
        Array2(const Array2 & temp) : row(temp.row), col(temp.col) {
            table = new int*[row];
            for (int i = 0; i < row; ++i) {
                table[i] = new int[col];
                for (int j = 0; j < col; ++j) table[i][j] = temp.table[i][j];
            } 
        }
        Array2 & operator=(const Array2 & temp){
            table = new int*[temp.row];
            for (int i = 0; i < temp.row; ++i) {
                table[i] = new int[temp.col];
                for (int j = 0; j < temp.col; ++j) table[i][j] = temp.table[i][j];
            } 
            return *this;
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