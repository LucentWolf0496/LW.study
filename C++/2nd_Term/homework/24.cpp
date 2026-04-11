#include <iostream>
using namespace std;


template <class T>
struct GoodCopy {

    // 当目标起点在源区间内部时，正向复制会“从前往后擦掉”后面的源数据；
    // 反向复制则从后往前，每次覆盖的都是已经处理过的尾部，因此安全。
    void operator()(const T* s, const T* e, T* t) {
        for (const T* p = e - 1; p >= s; --p) {
            *(t + (p - s)) = *p;
        }
    }

/*这里需要区分 指针常量 和 常量指针：
const T* s —— 指向常量的指针（pointer to constant）
指针本身可以改变（可以指向其他地址）
但不能通过该指针修改所指向的内容（即 *s = ... 不允许）
T* const s —— 常量指针（constant pointer）
指针本身不能改变（不能 ++s 或 s = ...）
但可以通过它修改所指向的内容（如果 T 不是 const*/

};

int a[200];
int b[200];
string c[200];
string d[200];

template <class T>
void Print(T s,T e) {
	for(; s != e; ++s)
		cout << * s << ",";
	cout << endl;
}

int main()
{
	int t;
	cin >> t;
	while( t -- ) {
		int m ;
		cin >> m;
		for(int i = 0;i < m; ++i)
			cin >> a[i];
		GoodCopy<int>()(a,a+m,b);
		Print(b,b+m);
		GoodCopy<int>()(a,a+m,a+m/2);
		Print(a+m/2,a+m/2 + m);

		for(int i = 0;i < m; ++i)
			cin >> c[i];
		GoodCopy<string>()(c,c+m,d);
		Print(c,c+m);
		GoodCopy<string>()(c,c+m,c+m/2);
		Print(c+m/2,c+m/2 + m);
	}
	return 0;
}