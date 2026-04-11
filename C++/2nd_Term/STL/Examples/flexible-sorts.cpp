// 用sort对结构数组进行排序
// sort使用规则如下：
/*
struct 结构名 {
    bool operator()( const T & a1,const T & a2) {
        //若a1应该在a2前面，则返回true。
        //否则返回false。 
    }
};
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct Student {
	char name[20];
	int id;
	double gpa;
};

Student students [] = {{"Jack",112,3.4},{"Mary",102,3.8},{"Mary",117,3.9},{"Ala",333,3.5},{"Zero",101,4.0}};

struct StudentRule1 { //按姓名从小到大排
	bool operator() (const Student & s1,const Student & s2) {// 直接使用重载，结构体无传入的参数，无需初始化处理
		if( stricmp(s1.name,s2.name) < 0)
			return true;
		return false;
	}
};

struct StudentRule2 { //按id从小到大排
	bool operator() (const Student & s1,const Student & s2) {
		return s1.id < s2.id;
	}
};

struct StudentRule3 { //按gpa从高到低排
	bool operator() (const Student & s1,const Student & s2) {
		return s1.gpa > s2.gpa;
	}
};

void PrintStudents(Student s[],int size){
	for(int i = 0;i < size;++i)
		cout << "(" << s[i].name << "," 
			<< s[i].id <<"," << s[i].gpa << ") " ;
	cout << endl;
}

int main(){
    int n = sizeof(students) / sizeof(Student);
    sort(students,students+n,StudentRule1()); //按姓名从小到大排
    PrintStudents(students,n);
    sort(students,students+n,StudentRule2()); //按id从小到大排
    PrintStudents(students,n);
    sort(students,students+n,StudentRule3()); //按gpa从高到低排
    PrintStudents(students,n);
    return 0;
}