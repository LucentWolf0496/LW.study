#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> digits = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // 生成所有可能的排列
    do {
        // 将排列分成三个三位数
        int num1 = digits[0] * 100 + digits[1] * 10 + digits[2];
        int num2 = digits[3] * 100 + digits[4] * 10 + digits[5];
        int num3 = digits[6] * 100 + digits[7] * 10 + digits[8];
        
        // 检查是否满足1:2:3的比例
        if (num1 * 2 == num2 && num1 * 3 == num3) {
            cout << num1 << " " << num2 << " " << num3 << endl;
        }
    } while (next_permutation(digits.begin(), digits.end()));// 函数降维打击
                                                             // 此函数两个功能
                                                             // 1.遍历数组全排列
                                                             // 2.在遍历完之前返回true使循环继续
                                                             //   之后就立刻返回false终止循环
    
    return 0;
}