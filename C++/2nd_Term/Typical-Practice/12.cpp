// 代理类对于三维数组的模拟，学一下这个代理类？？？
// 这个三维数组在内部是用 一维动态数组 存储所有元素，顺序为：
// 一维数组模拟三维数组————层（x）→ 行（y）→ 列（z）。
// 理解一维数组模拟三维数组时的内存连续性。
#include <iostream>
#include <iomanip> 
#include <cstring>
using namespace std;

template <class T>
class CArray3D {
private:
    int x, y, z;
    T* data;
public:
    CArray3D(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {
        data = new T[x * y * z];
    }
    ~CArray3D() {
        delete[] data;
    }
    
    // 代理类，表示一层（二维数组）
    class CArray2D {
    private:
        T* ptr;
        int y, z;
    public:
        CArray2D(T* p, int _y, int _z) : ptr(p), y(_y), z(_z) {}
        // 返回第 j 行的首地址
        T* operator[](int j) { return ptr + j * z; }
        const T* operator[](int j) const { return ptr + j * z; }
        // 隐式转换为 T*，用于 memset(a[1], ...)
        operator T*() { return ptr; }
        operator const T*() const { return ptr; }
    };
    
    CArray2D operator[](int i) { return CArray2D(data + i * y * z, y, z); }
    const CArray2D operator[](int i) const { return CArray2D(data + i * y * z, y, z); }
};

CArray3D<int> a(3,4,5);
CArray3D<double> b(3,2,2);

void PrintA(){
	for(int i = 0;i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for(int j = 0; j < 4; ++j) {
			for(int k = 0; k < 5; ++k) 
				cout << a[i][j][k] << "," ;
			cout << endl;
		}
	}
}

void PrintB(){
	for(int i = 0;i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for(int j = 0; j < 2; ++j) {
			for(int k = 0; k < 2; ++k) 
				cout << b[i][j][k] << "," ;
			cout << endl;
		}
	}
}

int main(){

	int No = 0;
	for( int i = 0; i < 3; ++ i ) {
		a[i];
		for( int j = 0; j < 4; ++j ) {
			a[j][i];
			for( int k = 0; k < 5; ++k )
				a[i][j][k] = No ++;
			a[j][i][i];	
		}
	}
	PrintA();
	memset(a[1],-1 ,20*sizeof(int));	
	memset(a[1],-1 ,20*sizeof(int));
	PrintA(); 
	memset(a[1][1],0 ,5*sizeof(int));	
	PrintA();
	for( int i = 0; i < 3; ++ i )
		for( int j = 0; j < 2; ++j )
			for( int k = 0; k < 2; ++k )
				b[i][j][k] = 10.0/(i+j+k+1);
	PrintB();
	int n = a[0][1][2];
	double f = b[0][1][1];
	cout << "****" << endl;
	cout << n << "," << f << endl;
		
	return 0;
}