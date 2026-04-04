#include <iostream>
using namespace std;

int main() {
    // 定义一个整数数组
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);  // 计算数组长度

    // 定义指针指向数组首元素
    int* ptr = arr;   // 等价于 int* ptr = &arr[0];

    // 使用指针遍历数组并输出每个元素
    cout << "数组元素为：";
    for (int i = 0; i < n; i++) {
        cout << *ptr << " ";   // 输出当前指针指向的元素
        ptr++;                  // 指针后移，指向下一个元素
    }
    cout << endl;

    // 也可以直接用指针算术访问，不修改指针本身
    ptr = arr;  // 重新指向开头
    cout << "再次输出：";
    for (int i = 0; i < n; i++) {
        cout << *(ptr + i) << " ";   // 通过偏移访问
    }
    cout << endl;

    return 0;
}