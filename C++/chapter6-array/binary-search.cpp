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
        else if (Key < AA[middle])
            high = middle - 1; // 由于从小到大，在下半区去找
        else
            low = middle + 1;// 由于从小到大，在上半区去找
    }
    return -1; //not found!在主函数中检测-1的退出标识符
}

int main()
{
    const int aSize = 100;
    int a[aSize];
    for (int i=0; i<aSize; i++)
    {
        a[i] = i*i + 1;// 给数组赋值为完全平方数+1
        cout << a[i] << ((i+1) % 10 == 0 ? "\n" : " ");// 输出数组，直观化代码
                                                       // 后续代码意思是每有10个数据就换行，整洁清晰
    }

    int searchKey;
    cout << "请输入一个待查正整数: ";
    cin >> searchKey;

    int b = 0;
    b = BinarySearch(a, searchKey, 0, aSize-1);

    if (b != -1)
        cout << "查到该数在数组中为: a[" << b << "]\n";// \n为换行标识符号
    else
        cout << "数组中无此数!\n";

    return 0;
}