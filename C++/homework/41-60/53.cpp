#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<vector<int>> matrix(n , vector<int>(n , 0));
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            cin >> matrix[i][j];
        }
    }
    int x1 = 0 , y1 = 0 , x2 = 0 , y2 = 0;
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            if (matrix[i][j] == 0){
                x1 = i;
                y1 = j;
                break;
            }
        }
    }
    for (int i = 0 ; i < n ; i ++){// 从0开始遍历，暴力无误
        if (matrix[x1][i] == 0)
            y2 ++;
    }
    for (int i = 0 ; i < n ; i ++){
        if (matrix[i][y1] == 0)
            x2 ++;
    }
    int sum = (x2 - 2) * (y2 - 2);
    cout << sum;
}