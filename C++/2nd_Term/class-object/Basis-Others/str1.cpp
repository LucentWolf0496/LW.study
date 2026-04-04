// string用于输入输出
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

int main(){
    string input("Input test 123 4.7 A");
    istringstream inputString(input);
    cout << inputString.str() << endl;
    string string1, string2;
    int i;
    double d;
    char c;
    inputString >> string1 >> string2 >> i >> d >> c;
    cout << string1 << endl << string2 << endl;
    cout << i << endl << d << endl << c <<endl;
    long L;
    if(inputString >> L) cout << "long\n";
    else cout << "empty\n";

	ostringstream outputString;// 其实没必要区分i/o，统一写stringstream其实就可以的
	int a = 10;
    outputString << "This " << a << "ok" << endl;
	cout << outputString.str() << endl;
}