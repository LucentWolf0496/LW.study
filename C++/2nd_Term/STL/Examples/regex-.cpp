// 关于正则表达式
// 正则表达式（Regular Expression，常简写为 regex 或 regexp）是一种用特定符号组合成的“模式”，
// 用来在文本中匹配、查找、替换符合某种规则的字符串。
// 可以把它理解为 “文本的模糊搜索规则”。
// 比如你想在一篇文章里找到所有像 abc123、xyz789 这种“3个字母+3个数字”的串，
// 写一个正则表达式就能一次性找到。
#include <iostream>
#include <regex> //使用正则表达式须包含此文件
using namespace std;
int main()
{
	regex reg("b.?p.*k");
	cout << regex_match("bopggk",reg) <<endl;//输出 1, 表示匹配成功
	cout << regex_match("boopgggk",reg) <<endl;//输出 0, 匹配失败
	cout << regex_match("b pk",reg) <<endl;   //输出 1, 表示匹配成功
	regex reg2("\\d{3}([a-zA-Z]+).(\\d{2}|N/A)\\s\\1"); 
	string correct="123Hello N/A Hello";
	string incorrect="123Hello 12 hello"; 
	cout << regex_match(correct,reg2) <<endl; //输出 1,匹配成功
	cout << regex_match(incorrect,reg2) << endl; //输出 0, 失败
}