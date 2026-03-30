#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main(){
    cerr << "FATAL ERROR————you are a crazy cat" << endl;// 报错标识输出
    freopen("class-object/111GUIDELINES.txt" , "r" , stdin);
    string s1 , s2 , s3;
    cin >> s1 >> s2 >> s3;
    cout << s1 << s2 << s3;
    int n = 10;
    cout << n << endl;
    cout << hex << n << '\n' // 16进制
         << dec << n << '\n' // 10进制
         << oct << n << '\n' // 8进制
         << dec << n << endl;
    double x = 10.0123124;
    cout.precision(5);
    // 默认情况下，precision 设置有效数字位数（总位数）
    // 与 fixed 结合，表示小数点后固定位数
    // 与 scientific 结合，科学计数法的小数部分位数
    cout << x << endl;  
    double x1 = 1234567.89,y = 12.34567;
	int n1 = 1234567;
	int m = 12;
	cout << setprecision(6) << x1 << endl << y << endl << n1 << endl << m;// x位数过多于是就写成科学计数法
    cout << setiosflags(ios::fixed) << 
			setprecision(6) << x << endl << 
			resetiosflags(ios::fixed)  << x ;// re————取消以小数点位置固定的方式输出

    int w = 4;    
    char string[10];    		
	cin.width(5);// 输入域宽要预留给'\0'一个位置，所以输入只读取4个字符
 	while(cin >> string){
	    cout.width(w++);// 输出域宽增加会保留空格来体现
		cout << string << endl;
		cin.width(5);
	}
    // 宽度设置有效性是一次性的，在每次读入和输出之前都要设置宽度。
}