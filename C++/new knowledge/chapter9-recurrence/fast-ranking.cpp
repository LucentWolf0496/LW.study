#include <iostream>
using namespace std;

void sort(int (&array)[], int zz, int yy){// 虽然可以传值，但是传引用更稳！
    int z, y, k;
    if (zz < yy){    // 如果 zz<yy，则需要排序
        z = zz; y = yy; k = array[z];
        do{
            // 右边的元素>k，让 y 往中间移
            while ((z < y) && (array[y] > k)){
                y = y - 1;
            }

            if (z < y){   // 不满足左边的元素>k
                array[z] = array[y];    // 让 array[y] 送给 array[z]
                z = z + 1;    // 同时让 z 往中间移
            }
            // 左边的元素<=k，让 z 往中间移
            while((z < y) && (array[z] <= k)){
                z = z + 1;
            }
            
            if (z < y){    // 不满足左边的元素<=k
                array[y] = array[z];
                y = y - 1;
            }
        } while (z != y);// 结束标志为精确到单个的do while循环，确保精确插空待排的数
        array[z] = k;    // k 已排到位
        sort(array, zz, z - 1);    // 递归，排左边部分
        sort(array, z + 1, yy);    // 递归，排右边部分，再次调用排被原有数据分开的两边数
    }
}

int main(){
    int a[10];
    cout << "请输入 10 个整数 \n";
    for (int i = 0; i < 10; i++)
        cin >> a[i];
    sort(a, 0, 9);    // 调用 sort 函数
    cout << "排序结果为:";
    for (int i = 0; i < 10; i++)
        cout << a[i] << ";";    // 输出排序结果
    cout << endl;
    return 0;
}