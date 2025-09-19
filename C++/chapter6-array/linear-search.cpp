#include <iostream>
using namespace std;

int LinearSearch(const int AA[], int key, int SizeofAA)// 二分查找函数设计，后续直接挪用
{
    for (int i = 0; i < SizeofAA; i++)
        if (AA[i] == key)
            return i;
    return -1;// 退出标识符号，主函数中检测到-1就退出
}

int main()
{
    int aSize = 10;
    int b = 0;
    int searchKey;
    const int a[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    
    cout << "输入一个待查正整数" << endl;
    cin >> searchKey;
    
    b = LinearSearch(a, searchKey, aSize);

    if (b != -1)
        cout << "查到该数在数组中为a["<< b << "]\n";// \n为换行符号
    else
        cout << "数组中无此数\n";
    
    return 0;
}