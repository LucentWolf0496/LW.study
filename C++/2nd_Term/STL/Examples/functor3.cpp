#include <list>
#include <iostream>
#include <iterator>
using namespace std;

class MyLess {
public:
	   bool  operator()( const int & c1, const int & c2 ) {
	   		  return (c1 % 10) < (c2 % 10);
	   }	   
};

int main(){	
	const int SIZE = 5;
	int a[SIZE] = {5,21,14,2,3};
	list<int> lst(a,a+SIZE);
	lst.sort(MyLess()); 
	ostream_iterator<int> output(cout,",");
	copy( lst.begin(),lst.end(),output); cout << endl;
	lst.sort(greater<int>()); //greater<int>()是个对象
  				        //本句进行降序排序
	copy( lst.begin(),lst.end(),output); cout << endl;
	return 0;
} 