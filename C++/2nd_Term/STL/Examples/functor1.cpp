#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>// 这个库里面含有函数对象accumulate，还有equal_to、greater、less
using namespace std;

int sumSquares( int total, int value)
{	return total + value * value;   }

template <class T>
void PrintInterval(T first, T last){ //输出区间[first,last)中的元素
	for( ; first != last; ++ first)
		cout << * first << " ";
	cout << endl;
}

template<class T> 
class SumPowers{
	private:
		int power; 
	public:
		SumPowers(int p):power(p) { }
		const T  operator() ( const T & total, 
	                                 const T & value) 
		{ //计算 value的power次方，加到total上
		 	T v = value;
			for( int i = 0;i < power - 1; ++ i)
				 v = v * value;  
	 		return total + v; 
		}
};

int main()  {
	const int SIZE = 10;	
	int a1[] = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> v(a1,a1+SIZE);
	cout << "1) "; PrintInterval(v.begin(),v.end());
	int result = accumulate(v.begin(),v.end(),0,sumSquares);
	int result1 = accumulate(v.begin(),v.end(),0,SumPowers<int>(2));
	cout << "2) 平方和：" << result << " " << result1 << endl;
	result = 
	  accumulate(v.begin(),v.end(),0,SumPowers<int>(3));  
	cout << "3) 立方和：" << result << endl;
	result = 
	  accumulate(v.begin(),v.end(),0,SumPowers<int>(4));  
	cout << "4) 4次方和：" << result;
	return 0;
}

// 该代码中两个实例化的例子如下：
// 实例化 = 用具体类型/值去填充模板参数，让编译器生成真正的代码。
// 没有实例化，模板就只是一个“模具”，不会出现在最终的二进制文件中。

/*
int result = accumulate(v.begin(),v.end(),0,SumSquares);
实例化出：
int accumulate(vector<int>::iterator first , vector<int>::iterator last , int init , int ( * op)( int,int)) {
	for ( ; first != last; ++first)
		init = op(init, *first);
    return init;
}
*/

/*
accumulate(v.begin(),v.end(),0,SumPowers<int>(3));  
实例化出：
int accumulate(vector<int>::iterator first , vector<int>::iterator last , int init , SumPowers<int> op) {
	for ( ; first != last; ++first)
		init = op(init, *first);
    return init;
}
*/