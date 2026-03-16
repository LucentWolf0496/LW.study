// 赋值运算符 ‘=’重载
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class String {
	private:  
	        char * str;
	public:
		String ():str(new char[1]) { str[0] = 0;}
		const char * c_str() { return str; };
		String & operator = (const char * s);
		~String( ) { delete [] str; }
};
String & String::operator = (const char * s) 
{			//重载“=”以使得 obj = “hello”能够成立
		delete [] str;
		str = new char[strlen(s)+1];
		strcpy( str, s);
		return * this;
}

int main()
{
    String s;
    s = "Good Luck," ; //等价于 s.operator=("Good Luck,");
    cout << s.c_str() << endl;
 // String s2 = "hello!";   //这条语句要是不注释掉就会出错
    s = "Shenzhou 8!"; //等价于 s.operator=("Shenzhou 8!");
    cout << s.c_str() << endl;
    return 0;
}