#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<vector<int>> matrix(n , vector<int>(n));
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            cin >> matrix[i][j];
        }
    }
    int count1 = 0 , count2 = 0;
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            if (matrix[i][j] <= 50){
                count1 ++;
                count2 ++;
                if (i >= 1 && i <= n - 2 && j >= 1 && j <= n - 2 // 小心，不要打错变量名字！！！
                    && matrix[i + 1][j] <= 50 && matrix[i - 1][j] <= 50
                    && matrix[i][j + 1] <= 50 && matrix[i][j - 1] <= 50)
                    count2 --;
            }
        }
    }
    cout << count1 << " " << count2 << endl;
    return 0;
}