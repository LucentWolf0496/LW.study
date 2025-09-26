#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    for (int i = 1 ; i <= n ; i ++){
        vector<vector<int>> matrix(n , vector<int>(n));
        for (int j = 0 ; j < n ; j ++){
            for (int k = 0 ; k < n ; k ++){
                cin >> matrix[j][k];
            }
        }
        int sum = 0;
        while (matrix.size() > 1){
            for (int j = 0 ; j < matrix.size() ; j ++){
                int temp = matrix[j][0];// 好方法，求最大最小的时候都以第一个元素作为temp，一一和temp比
                for (int k = 0 ; k < matrix.size() ; k ++){
                    if (matrix[j][k] <= temp){
                        temp = matrix[j][k];
                    }
                }
                for (int k = 0 ; k < matrix.size() ; k ++){
                    matrix[j][k] -= temp;
                }
            }
            for (int j = 0 ; j < matrix.size() ; j ++){
                int temp = matrix[0][j];// 好方法，求最大最小的时候都以第一个元素作为temp，一一和temp比
                for (int k = 0 ; k < matrix.size() ; k ++){
                    if (matrix[k][j] <= temp){
                        temp = matrix[k][j];
                    }
                }
                for (int k = 0 ; k < matrix.size() ; k ++){
                    matrix[k][j] -= temp;
                }
            }
            sum += matrix[1][1];
            matrix.erase (matrix.begin() + 1);// 擦除行直接擦matrix，行就是matrix的元素
            for (int j = 0 ; j < matrix.size() ; j ++){
                matrix[j].erase (matrix[j].begin() + 1);// 擦除列需要处理matrix[j]，j需要遍历
                                                        // 列是matrix[j]的元素，辨析与行的区别！！！
            }
        }
        cout << sum << endl;
    }
}