#include <iostream>
#include <vector>
using namespace std;

int main(){
    int a = 0 , b = 0;
    cin >> a >> b;
    vector<vector<int>> matrix(a , vector<int>(b));
    for (int i = 0 ; i < a ; i ++){
        for (int j = 0 ; j < b ; j ++){
            int temp = 0;
            cin >> temp;
            matrix[i][j] = temp;
        }
    }
    int count = a * b;
    int x = 0;
    do{
        for (int i = x ; i < b - x ; i ++){
            cout << matrix[x][i] << endl;
            count --;
        }
        if (count == 0)
            break;
        for (int i = 1 + x ; i < a - x ; i ++){
            cout << matrix[i][b - 1 - x] << endl;
            count --;
        }
        if (count == 0)
            break;
        for (int i = b - 2 - x ; i >= x ; i --){
            cout << matrix[a - 1 - x][i] << endl;
            count --;
        }
        if (count == 0)
            break;
        for (int i = a - 2 - x ; i >= 1 + x ; i --){
            cout << matrix[i][x] << endl;
            count --;
        }
        if (count == 0)
            break;
        x ++;
    }while (true);
    return 0;
}