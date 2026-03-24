// 类与对象+指针的二维数组模拟程序
#include <iostream>
using namespace std;

class Array{
    private:
        int **table;
        int row;
        int col;
    public:
        Array(){ table = NULL; row = 0; col = 0; }
        Array(int x , int y): row(x) , col(y){
            if (x != 0 && y != 0){
                table = new int*[x];
                for (int i = 0 ; i < x ; i ++) table[i] = new int[y];
            }
            else table = NULL;
        }
        Array(const Array& x){
            row = x.row;
            col = x.col;
            if (x.table){
                table = new int*[row];
                for (int i = 0 ; i < row ; i ++) table[i] = new int[col];
                for (int i = 0 ; i < row ; i ++) for (int j = 0 ; j < col ; j ++) table[i][j] = x.table[i][j];
            }
            else table = NULL;
        }
        int* & operator[](int x){return table[x];}
        int & operator()(int x , int y){return table[x][y];}
};

int main(){
    Array temp1(3 , 4);
    for (int i = 0 ; i < 3 ; i ++){
        for (int j = 0 ; j < 3 ; j ++){
            temp1[i][j] = i + j * j;
        }
        temp1(i , 3) = 555;
    }
    Array temp2(temp1);
    Array temp3 = temp1;
    for (int i = 0 ; i < 3 ; i ++){
        for (int j = 0 ; j < 3 ; j ++){
            cout << temp2[i][j] << " ";
        }
        cout << temp2(i , 3);
        cout << endl;
    }
    cout << endl;
    for (int i = 0 ; i < 3 ; i ++){
        for (int j = 0 ; j < 3 ; j ++){
            cout << temp3[i][j] << " ";
        }
        cout << temp3(i , 3);
        cout << endl;
    }
}