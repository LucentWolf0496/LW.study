// 无序容器(哈希表)————哈希表插入和查询的时间复杂度几乎是常数
// 头文件 <unordered_map> 实现哈希表
// 哈希表简介：
// 哈希表是一种通过“哈希函数”将键（key）映射到存储位置的数据结构，用来快速存储和查找键值对（key-value pair）。
// 哈希表 = 能把任意键（如字符串）“哈希”成一个整数下标，从而实现近乎常数时间的插入和查找。
// 代码中的 unordered_map 就是 C++ 给出的哈希表，适合需要快速键值查找、不关心元素顺序的场景。
// 在 C++ 中，unordered_map 就是哈希表实现，名字中的 unordered 表示元素无序（不同于 map 的红黑树有序结构），内部存储pair。

// 哈希函数：
// 哈希函数 = 把任意键“杂乱化”成一个整数的算法，要求快且均匀，让哈希表能快速定位数据。
// C++ 的 unordered_map 已经为常见类型内置了这样的函数，你也可以为自己的类型定制。
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
int main()
{
    unordered_map<string,int> turingWinner; //图灵奖获奖名单
	turingWinner.insert(make_pair("Dijkstra",1972));
	turingWinner.insert(make_pair("Scott",1976));
	turingWinner.insert(make_pair("Wilkes",1967));
	turingWinner.insert(make_pair("Hamming",1968));
	turingWinner["Ritchie"] = 1983;
	string name;
	cin >> name; //输入姓名
    unordered_map<string,int>::iterator p = turingWinner.find(name);
	//据姓名查获奖时间
	if( p != turingWinner.end())
		cout << p->second;
	else
		cout << "Not Found" << endl;
	return 0;
}