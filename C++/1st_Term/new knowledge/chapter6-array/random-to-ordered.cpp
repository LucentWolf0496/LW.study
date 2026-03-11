// 非常原始的先排序再搜索程序
// 现代c++中排序可以用vector，sort，greater完成！
#include <iostream>
using namespace std;

int BinarySearch(int AA[], int Key, int low, int high)
{
    int middle = 0;
    while (low <= high)
    {
        middle = (low + high) / 2;//注意整数除法，序号均为整数
        if (Key == AA[middle]) // 直接出序号，为middle位
            return middle;
        else if (Key < AA[middle])// 这个小于是对升序使用二分搜索，大于则是对于降序使用
            high = middle - 1; // 由于从小到大，在下半区去找
        else
            low = middle + 1;// 由于从小到大，在上半区去找
    }
    return -1; //not found!在主函数中检测-1的退出标识符
}

void order(int a[] , int size)// 定义数组的时候要设置形参
                              // 使用void表明对数组进行操作，以防“数组”是一个难以return的事物
{
    int i = 0, j = 0, p = 0;
    
    for (j = 0; j < size - 1; j++)    // 冒泡排序，外层循环
    {
        for (i = 0; i < size - j - 1; i++)    // 内层循环
        {
            if (a[i] > a[i+1])    // 如果a[i] > a[i+1], 从而实现从小到大排列！小心！
                                  // 升序排列使用二分法/降序排列使用二分法有不同，本代码二分法对应的是升序
            {
                p = a[i];    // 让a[i]与a[i+1]交换
                a[i] = a[i+1];
                a[i+1] = p;
            }
        }
    }
    return;// 执行完对数组的加工就返回主函数
}

int main()
{
    const int aSize = 10;
    int a[aSize];
    for (int i=0; i<aSize; i++)
    {
        int x = 0;
        cin >> x;
        a[i] = x;
    }
    
    int searchKey;
    cout << "请输入一个待查正整数: ";
    cin >> searchKey;
    
    order (a , aSize);// 此处以数组为自变量就直接输入数组名字即可

    int b = 0;
    b = BinarySearch(a, searchKey, 0, aSize-1);

    if (b != -1)
        cout << "查到该数从小到大排序是第" << b + 1 << "个\n";// \n为换行标识符号
                                                            // 在终点将零基数组的序号转为正常序数，防止数组阶段出现bug！
    else
        cout << "数组中无此数!\n";
    
    return 0;
}