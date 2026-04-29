#include <iostream>
#include <set> 
using namespace std;
int main()     {
	typedef set<int>::iterator IT;
	int a[5] = { 3,4,6,1,2 };
	set<int> st(a,a+5);    // st里是 1 2 3 4 6
	pair< IT,bool> result;
	result = st.insert(5);  // st变成  1 2 3 4 5 6
	if( result.second )     //插入成功则输出被插入元素
	      cout << * result.first  << " inserted" << endl; //输出: 5 inserted
	if((result = st.insert(5)).second )  
	      cout << * result.first  << endl;
	else
	      cout << * result.first << " already exists" << endl; //输出 5 already exists
	pair<IT,IT> bounds = st.equal_range(4);
	cout << * bounds.first << "," << * bounds.second ;     //输出：4,5
	return 0;
}

/*
对于 std::set，单参数版本的 insert 成员函数返回值是 std::pair<iterator, bool>。
iterator 指向被插入的元素（若插入成功）或已存在的等值元素（若插入失败）。
bool 表示插入是否成功：true 表示成功插入新元素，false 表示集合中已存在相同键值的元素，此时不会修改集合。
而 std::multiset 的 insert 返回的是单纯的 iterator（因为允许重复，总是成功插入）。
*/