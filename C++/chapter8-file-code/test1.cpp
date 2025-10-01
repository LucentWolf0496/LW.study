#include <fstream>
#include <iostream>
using namespace std;

struct student
{
    char name[20];    //姓名
    char sex;    //性别
    unsigned long birthday;  //生日
    float height;    //身高
    float weight;    //体重
};

int main()
{
    student room[4] = {    //定义student结构数组，并初始化
        {"Lixin", 'M', 19840318, 1.82, 65.0},
        {"Zhangmen", 'M', 19840918, 1.75, 58.0},
        {"Helei", 'M', 19841209, 1.83, 67.1},
        {"Geyujian", 'M', 19840101, 1.70, 59.0}
    };
    
    //将数据输出到 Student.txt 文件中
    ofstream fout("D:\\Project-leaf\\LW.study\\C++\\chapter8-file-code\\Student.txt");   
    //定义输出文件流
    //指定路径到工作区，注意双右斜杠！！！
    if (!fout)    //判断文件是否已打开
    {
        cout << "文件打开失败\n";
        return 0;
    }
    
    for (int i = 0; i < 4; i++)    //将学生数据写入文件
        fout << room[i].name
             << room[i].sex
             << room[i].birthday
             << room[i].height
             << room[i].weight << endl;

    fout.close();    //关闭文件
    return 0;
}