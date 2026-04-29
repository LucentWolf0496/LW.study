#include <iostream>
#include <map>
using namespace std;

template <class Key,class Value>
ostream & operator <<( ostream & o, const pair<Key,Value> & p)
{
	o << "(" << p.first  << "," << p.second << ")";
	return o;
}

int main()  {
	typedef map<int, double,less<int> > mmid;
	mmid pairs;
	cout << "1) " << pairs.count(15) << endl;
	pairs.insert(mmid::value_type(15,2.7));
	pairs.insert(make_pair(15,99.3));
    // make_pair生成一个pair对象
    // map 的 insert 方法不会覆盖已存在的键，而下标运算符 [] 允许修改。
	cout << "2) " << pairs.count(15) << endl;
	pairs.insert(mmid::value_type(20,9.3));
	mmid::iterator i;
	cout << "3) ";
	for( i = pairs.begin(); i != pairs.end();i ++ )
		cout << * i  << ",";
	cout << endl;
	cout << "4) ";
	int n =  pairs[40];//如果没有关键字为40的元素，则插入一个
	for( i = pairs.begin(); i != pairs.end();i ++ )
		cout << * i  << ",";
	cout << endl;
	cout << "5) ";
	pairs[15] = 6.28;
    //把关键字为15的元素值改成6.28
    // map 的 insert 方法不会覆盖已存在的键，而下标运算符 [] 允许修改。
	for( i = pairs.begin(); i != pairs.end();i ++ )
		cout << * i  << ",";
}