#include <iostream>
#include <algorithm>
using namespace std;
class A   {
      public:   int n;
      A(int i):n(i) { }
};

bool operator<( const A & a1, const A & a2) {
	 cout << "< called,a1=" 
		<< a1.n << " a2=" << a2.n << endl;
	 if( a1.n == 3 && a2.n == 7)// 自定义的重载的神奇比较方式
		     return true;
	 return false;
}

int main()  {
  A aa[] = { 3,5,7,2,1};
  cout << min_element(aa,aa+5)->n << endl;
  cout << max_element(aa,aa+5)->n << endl; 
  return 0;    
}