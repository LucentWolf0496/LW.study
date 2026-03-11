#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

int kaprekar_process(int num) {
    // 将数字转换为字符串并确保有4位（前面补零）
    ostringstream oss;
    oss << setw(4) << setfill('0') << num;
    string num_str = oss.str();
    
    // 对数字进行排序（升序和降序）
    string asc = num_str;
    string desc = num_str;
    
    sort(asc.begin(), asc.end());
    sort(desc.begin(), desc.end(), greater<char>());
    
    // 转换为整数
    int min_num = stoi(asc);
    int max_num = stoi(desc);
    
    return max_num - min_num;
}

int main() {
    int num;
    cout << "请输入一个四位数: ";
    cin >> num;
    
    // 检查是否所有数字相同
    ostringstream oss;
    oss << setw(4) << setfill('0') << num;
    string num_str = oss.str();
    
    if (num_str[0] == num_str[1] && num_str[1] == num_str[2] && num_str[2] == num_str[3]) {
        cout << "所有数字相同，不会收敛到6174" << endl;
        return 0;
    }
    
    cout << "验证过程:" << endl;
    int count = 0;
    while (num != 6174 && count < 10) {
        int next = kaprekar_process(num);
        cout << setw(4) << setfill('0') << num << " → " 
             << setw(4) << setfill('0') << next << endl;
        num = next;
        count++;
    }
    
    if (num == 6174) {
        cout << "经过 " << count << " 步后收敛到6174" << endl;
    } else {
        cout << "未能在10步内收敛到6174" << endl;
    }
    
    return 0;
}