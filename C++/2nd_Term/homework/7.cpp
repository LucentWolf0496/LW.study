#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if( s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;

	}
	~MyString() { if(p) delete [] p; }
// 在此处补充你的代码
    void Copy(const char * x){
        if (x){
            p = new char[strlen(x) + 1];
            strcpy(p,x);
        }
        else p = NULL;
    }
    friend ostream & operator<<(ostream & os , const MyString &s){
        os << s.p;
        return os;
    }
    MyString & operator=(const MyString &s){
        char * p0 = s.p;
        if( p0) {
			p = new char[strlen(p0) + 1];
			strcpy(p,p0);
		}
		else
			p = NULL;
        return *this;
    }
    MyString & operator=(const char * x){
        if (x){
            p = new char[strlen(x) + 1];
            strcpy(p,x);
        }
        else p = NULL;
        return *this;
    }
};
int main()
{
	char w1[200],w2[100];
	while( cin >> w1 >> w2) {
		MyString s1(w1),s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;
		
	}
}