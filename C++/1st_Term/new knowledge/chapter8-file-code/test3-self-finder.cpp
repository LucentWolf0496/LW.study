#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
    ifstream fin(__FILE__);  // 打开当前源文件
    if (!fin) {
        cout << "无法打开文件" << endl;
        return 1;// 表示程序异常结束
    }
    int count = 0;
    string line;   
    while (getline(fin, line)) {// 逐行读取文件内容，与cin >> 区别，逐行读取包括空格       
        for (char c : line) {// 统计当前行中字符 'o' 的数量，可换成任意字符，换字符串则需改变量类型
            if (c == 'o') {
                count++;
            }
        }
    }
    fin.close();  // 关闭文件
    cout << "本程序中字符 'o' 的个数为: " << count << endl; 
    return 0;// 表示程序正常结束
}