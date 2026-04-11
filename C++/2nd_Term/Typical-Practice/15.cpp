// 反转题目，直接对指针进行“折半”操作，不要新建临时变量导致操作无效
#include <iostream>
using namespace std;

template<class T>
void f1(T *list, int size) {
    for (int i = 0; i < size / 2; ++i) {
        T temp = list[i];
        list[i] = list[size - i - 1];
        list[size - i - 1] = temp;
    }
    // 如果要引入临时变量result，需要
    // 1）使用指针的引用 
    // 2）或者一个一个进行赋值————for (int i = 0; i < size; ++i) {list[i] = result[i];}
}

// 另一个版本：使用临时指针result进行操作
template<class T>
void f2(T *list, int size) {
    T *result = new T[size];
    for (int i = 0; i < size; ++i) {
        result[i] = list[size - i - 1];
    }
    // 将 result 的内容复制回 list 指向的内存————关键：要一个一个复制
    for (int i = 0; i < size; ++i) {
        list[i] = result[i];
    }
    delete[] result;
}

int main(){
	int a[5] = { 10, 21, 34, 4, 50 };
	double d[6] = { 4.1, 11.1, 10.1, 9.1, 8.1, 7.1 };
	f1(a, 5);
	f2(d, 6);
	for (int i = 0; i < 5; i++){
		cout << a[i] << " ";
	}
	cout << endl;
	for (int j = 0; j < 6; j++){
		cout << d[j] << " ";
	}
	cout << endl;
	return 0;
}