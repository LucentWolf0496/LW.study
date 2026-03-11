// 在这段代码中，构造函数是在类 Test 的定义内部直接给出的
// 因此不需要使用 Test::Test 这样的类外定义形式。
#include <iostream>
using namespace std;

class  Test {
	public:
		Test( int n) { }             //(1)————注：大括号里面就是初始化函数的内容，只是这个代码仅作演示，并未设置private变量和初始函数
		Test( int n, int m) { }      //(2) 
        Test() { }                   //(3)
};// 记得打上分号

int main(){
    Test  array1[3] = { 1, Test(1,2) }; // 三个元素分别用(1),(2),(3)初始化 
    Test  array2[3] = { Test(2,3), Test(1,2) , 1}; // 三个元素分别用(2),(2),(1)初始化 
    Test  * pArray[3] = { new Test(4), new Test(1,2) }; //两个元素分别用(1),(2) 初始化 
}