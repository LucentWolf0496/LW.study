#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int main()  {   //find算法示例
	int array[10] = {10,20,30,40};
	vector<int> v;
	v.push_back(1);	v.push_back(2);
	v.push_back(3);	v.push_back(4);
	vector<int>::iterator p;
	p = find(v.begin(),v.end(),3);
	if( p != v.end())
		cout << * p << endl; //输出3
    p = find(v.begin(),v.end(),9);
	if( p == v.end())
		cout << "not found " << endl;
	p = find(v.begin()+1,v.end()-2,1); 
	//整个容器：[1,2,3,4]， 查找区间：[2,3)
	if( p != v.end())// 指向的是区间的末尾，而不是整个v的末尾，所以输出区间的末尾3

    /*v.end() 返回的迭代器指向最后一个元素之后的位置（past-the-end），并不指向任何有效元素。
    它通常用于表示“终点”，在循环中作为停止标志（例如 it != v.end()）。
    对 v.end() 解引用（*v.end()）是未定义行为，千万不要这样做。*/
    
		cout << * p << endl;
	int * pp = find( array,array+4,20);//数组名是迭代器,但vector名字不是迭代器
	cout << * pp << endl;
}