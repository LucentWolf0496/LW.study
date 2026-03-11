#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
private:
    string name;
    int age;
    int code;
    int score1;
    int score2;
    int score3;
    int score4;
    float aver;

public:
    void input(){
        char comma;
        cin >> age >> comma >> code >> comma >> score1 >> comma >> score2 >> comma >> score3 >> comma >> score4;
    }
 
    void calculate(){
        aver = (score1 + score2 + score3 + score4) / 4.0;
    }
    
    void output(){
        cout << name << "," << age << "," << code << "," << aver << endl;
    }
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}