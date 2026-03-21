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
            table = new int*[x];
            for (int i = 0 ; i < x ; i ++) table[i] = new int[y];
        }
};