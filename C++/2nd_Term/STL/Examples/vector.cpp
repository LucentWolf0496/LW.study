// vector程序示例，加入了迭代器和模板的升级版vector使用案例
// 从vector到deque：
// 所有适用于 vector的操作都适用于 deque。
// deque还有 push_front（将元素插入到前面）和 pop_front(删除最前面的元素）操作，复杂度是O(1)
#include <iostream>
#include <vector> 
using namespace std;

template<class T>// 使用模板和迭代器的vector打印函数
void PrintVector( T s, T e){ 
	for(; s != e; ++s)
		cout << * s << " "; 
	cout << endl;
}

int main()  {	
	int a[5] = { 1,2,3,4,5 };    
	vector<int> v(a,a+5);  //将数组a的内容放入v
	cout << "1) " << v.end()  - v.begin() << endl; 
	//两个随机迭代器可以相减，输出 1) 5
	cout << "2) "; PrintVector(v.begin(),v.end()); // begin和end是vector的迭代器
	//2) 1 2 3 4 5
	v.insert(v.begin() + 2, 13); //在begin()+2位置插入 13
	cout << "3) "; PrintVector(v.begin(),v.end()); 
	//3) 1 2 13 3 4 5
	v.erase(v.begin() + 2); //删除位于 begin() + 2的元素 
	cout << "4) "; PrintVector(v.begin(),v.end()); 
	//4) 1 2 3 4 5
	vector<int> v2(4,100);  //v2 有4个元素，都是100
	v2.insert(v2.begin(),v.begin()+ 1,v.begin()+3);
	//将v的一段插入v2开头
	cout << "5) v2: "; PrintVector(v2.begin(),v2.end()); 
	//5) v2: 2 3 100 100 100 100
	v.erase(v.begin() + 1, v.begin() + 3); 
	//删除 v 上的一个区间,即 2,3 
	cout << "6) "; PrintVector(v.begin(),v.end()); 
	//6) 1 4 5
	return 0;
}
