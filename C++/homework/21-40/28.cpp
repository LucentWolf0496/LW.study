#include <iostream>
using namespace std;

int main()
{
    //part1：输入abc并给矩阵下定义
    int a , b , c = 0;
    cin >> a >> b >> c;
    int matrix1[a][b];
    int matrix2[b][c];
    int matrix3[a][c];
    int sum = 0;
    // part2：输入两个矩阵
    for (int i = 0 ; i <= a - 1 ; i ++)
    {
        for (int j = 0 ; j <= b - 1 ; j ++)
        {
            cin >> matrix1[i][j];
        }
    }
    for (int i = 0 ; i <= b - 1 ; i ++)
    {
        for (int j = 0 ; j <= c - 1 ; j ++)
        {
            cin >> matrix2[i][j];
        }
    }
    // part3：计算矩阵乘法每一项，注意sum值在算完之后要归零
    for (int i = 0 ; i <= a - 1 ; i ++)
    {
        for (int j = 0 ; j <= c - 1 ; j ++)
        {
            for (int k = 0 ; k <= b - 1 ; k ++)
            {
                sum = sum + matrix1[i][k] * matrix2[k][j];
            }
            matrix3[i][j] = sum;
            sum = 0;
        }
    }
    // part4：输出，记得要审题符合规范，通过单独输出第一项来防止空格干扰
    for (int i = 0 ; i <= a - 1 ; i ++)
    {
        cout << matrix3[i][0];
        for (int j = 1 ; j <= c - 1 ; j ++)
        {
            cout << " " << matrix3[i][j];
        }
        cout << endl;
    }
    return 0;
}