#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>// sort函数，利用<运算
using namespace std;
class MyString:public string
{
	private:
		string str = "";
	public:
		MyString(){  };
		MyString(string s){
			str = s;
		}
		MyString(const MyString & x){
			str = x.str;
		}
		MyString(const char * x){
			str = x;// char*类型和string类型是高度兼容的，允许赋值和运算
		}
		MyString & operator=(const char * x){
			str = x;
			return *this;
		}
		MyString & operator=(const MyString x){
			str = x.str;
			return *this;
		}
		char & operator[](int x){
			return str[x];
		}
		string operator()(int x , int y){
			string temp = str.substr(x , y);
			return temp;
		}
		friend ostream & operator<<(ostream & os , MyString x){
			os << x.str;
			return os;
		}
		friend MyString operator+(const MyString & x , const MyString & y){
			string temp = x.str + y.str;
			MyString result;
			result.str = temp;
			return result;
		}
		friend MyString operator+(const MyString & x , const char* y){
			string temp = x.str + y;
			MyString result;
			result.str = temp;
			return result;
		}
		friend MyString operator+(const char* x , const MyString & y){
			string temp = x + y.str;
			MyString result;
			result.str = temp;
			return result;
		}
		MyString operator+=(const char* y){
			string temp = str + y;
			str = temp;
			return *this;
		}
		friend bool operator<(MyString x , MyString y){// 用于sort的比较，这个比较实际是利用<算符，所以需要对<进行重载
			return x.str < y.str;
		}
};


int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
        sort(SArray,SArray+4);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}