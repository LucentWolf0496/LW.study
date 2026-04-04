// 二进制文件读写————从键盘输入几个学生的姓名的成绩，并以二进制文件形式保存
#include <iostream>
#include <fstream>
using namespace std;
struct Student {
		char name[20];
		int score;
};

int main()  {
	Student s;		
	ifstream inFile("students.dat",ios::in | ios::binary );
	if(!inFile) {
		cout << "error" <<endl;
		return 0;
	}
	while( inFile.read( (char* ) & s, sizeof(s) ) ) {
	    int readedBytes = inFile.gcount(); //看刚才读了多少字节
		cout << s.name << " " << s.score << endl;	
	}
	inFile.close();
	return 0; 
}