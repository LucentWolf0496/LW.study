#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    int count = 1;
    int up = n * n;
    vector<vector<int>> matrix(n , vector<int>(n , 0));
    int x = 0 , y = (n - 1) / 2;// 分清楚行和列，x是行，y是列
    while (count <= up){
        if(x != 0 && y != n - 1){
            matrix[x][y] = count;// 将矩阵赋值放在分支之内，避免一次赋值矩阵导致多次x，y的位置判断
            count ++;
            if (matrix[x - 1][y + 1] != 0)
                x = x + 1;
            else{
                x = x - 1;
                y = y + 1;
            }
        }
        if (x == 0 && y == n - 1){
            matrix[x][y] = count;
            count ++;
            x = x + 1;
        }
        if (x == 0 && y != n - 1){
            matrix[x][y] = count;
            count ++;
            x = n - 1;
            y = y + 1;
        }
        if (x != 0 && y == n - 1){
            matrix[x][y] = count;
            count ++;
            x = x - 1;
            y = 0;
        }
    }
    for (int i = 0 ; i < n ; i ++){
        cout << matrix[i][0];// 经典答题模板。考虑空格，先输出一个无空格的
        for (int j = 1 ; j < n ; j ++){// 注意这里j = 1的初始值
            cout << " " << matrix[i][j];
        }
        cout << endl;
    }
    return 0;
}