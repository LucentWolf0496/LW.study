// 警告！！！
// 本代码为教材例题，索引1-6是为了服务表达清晰度，使cout时的编号与序数一致
// 但实际上数组的索引是零基的，所以实际使用时应该从0开始对i，j冒泡遍历以排大小
// 同时这是从大到小排序，应根据情景需求灵活调整＞/＜符号
#include <iostream>
#include <memory>
using namespace std;

int main()
{
    int i = 0, j = 0, p = 0, a[7];
    for (i = 1; i <= 6; i++)    // 输入6个数，放入a数组中
    {
        cout << "请输入待排序的数 a[" << i << "]=";
        cin >> a[i];
    }
    
    for (j = 1; j <= 5; j++)    // 冒泡排序，外层循环
    {
        for (i = 1; i <= 6 - j; i++)    // 内层循环
        {
            if (a[i] < a[i+1])    // 如果a[i] < a[i+1]
            {
                p = a[i];    // 让a[i]与a[i+1]交换
                a[i] = a[i+1];
                a[i+1] = p;// 实现从大到小的排列
            }
        }
    }

    for (i = 1; i <= 6; i++)    // 输出排序结果
    {
        cout << a[i] << endl;
    }
    
    return 0;
}