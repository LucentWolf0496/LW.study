#include <iostream>
#include <cstring>
using namespace std;

// 定义学生结构体
struct student {
    char name[20];
    char sex;
    unsigned long birthday;
    float height;
    float weight;
};

int main() {
    // 定义并初始化结构体数组
    student room[4] = {
        {"Lixin", 'M', 19840318, 1.82, 65.0},
        {"Zhangmen", 'M', 19840918, 1.75, 58.0},
        {"Helei", 'M', 19841209, 1.83, 67.1},
        {"Geyujian", 'M', 19840101, 1.70, 59.0}
    };

    student q;  // 临时变量用于交换
    
    // 使用冒泡排序按生日排序
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3 - j; i++) {
            if (room[i].birthday > room[i+1].birthday) {
                q = room[i];
                room[i] = room[i+1];  // 修正：原代码为 Room[i+1]
                room[i+1] = q;
            }
        }
    }
    
    // 输出排序后的结果
    for (int i = 0; i < 4; i++) {
        cout << room[i].name << "\n"
             << room[i].sex << "\n"
             << room[i].birthday << "\n"
             << room[i].height << "\n"
             << room[i].weight << "\n\n";
    }
    
    return 0;
}