// 对string对象的实验性探索如下：
// 通过不安全、不可移植的指针操作，演示 std::string 内部并不是只存一个字符串数据，
// 而是在对象本身之外（或之内）还存放了长度、容量等元数据，并且这些数据可以通过内存布局的方式“猜”出来。
// string 不是简单的字符数组
// 它内部有额外的状态信息，被类给连同这个字符数组给封装了起来，string 的长度存在字符串数据的前面，而不是靠 '\0' 计算。
// 直接修改 c_str() 返回的内存是危险且不可预期的
#include <iostream>
using namespace std;

int main(){
	string s1("1267");
	cout << "sizeof string = " << sizeof(s1) << endl;
    // 不受具体string影响，因为sizeof输出的是指针的大小————32

    // 看看string对象里放的东西是不是 c_str()返回的指针: 
	string s2("123568");
	cout << "sizeof string = " << sizeof(s2) << endl;
	char * * p =  (char * * ) & s2;
	char * pstr1 = (char *) s2.c_str();
	printf("p=%p,pstr=%p\n",* p,pstr1);
	cout << pstr1 << endl;

	string s3("12345678");
	cout << "sizeof string = " << sizeof(s3) << endl;
	char * pstr2 = (char *) s3.c_str();
	pstr2[3] = '0';
    cout << pstr2 << endl;
	pstr2[4] = 0;// 这是对内存地址的处理，所以会改变s3的值。0是字符串截断标志，会被隐式转换为'\0'，导致pstr2输出截断
	cout << pstr2 << endl;
	cout << s3 << endl;
	cout << s3.length() << endl;
	return 0; 
}