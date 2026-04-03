// 二进制文件读写

// 二进制读文件：
// ifstream 和 fstream的成员函数：
// istream& read (char* s, long n);
// 将文件读指针指向的地方的n个字节内容，读入到内存地址s，然后将文件读指针向后移动n字节 
// (以ios::in方式打开文件时，文件读指针开始指向文件开头)。

// 二进制写文件：
// ofstream 和 fstream的成员函数：
// ostream& write (const char* s, long n);
// 将内存地址s处的n个字节内容，写入到文件中写指针指向的位置，然后将文件写指针向后移动n字节
// (以ios::out方式打开文件时，文件写指针开始指向文件开头, 以ios::app方式打开文件时，文件写指针开始指向文件尾部)。

// 在文件中写入和读取一个整数
#include <iostream>
#include <fstream>
using namespace std;
int main(){  
	ofstream fout("some.dat", ios::out | ios::binary);
	int x=120;
	fout.write( (const char *)(&x), sizeof(int) );
    //(const char *)(&x) 将 int* 强制转换为 const char*，
    //这是 write 函数要求的参数类型——它需要一块连续内存的起始地址，按字节原样写入。
	fout.close();
	ifstream fin("some.dat",ios::in | ios::binary);
	int y;
	fin.read((char * ) & y,sizeof(int));
    // 这里y就不能const，因为是待读取的变量，要读入120
	fin.close();
	cout << y <<endl;
	return 0;
}