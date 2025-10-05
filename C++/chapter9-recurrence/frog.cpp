#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int s , y;
    cin >> s >> y;
    int n = pow(2 , s) * (y + 1);
    cout << n << endl;
}

// 此代码简单，但重在思维
// 从1个柱子入手分析直到发现“柱子”可作为“容器”容纳青蛙，从而达成递推
// 再新定义出“基础量”和“0个柱子”情况，均为y + 1
// 累加式递推，得出表达式