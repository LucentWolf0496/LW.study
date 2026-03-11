#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    int count = 1;
    bool check = false;
    vector<vector<int>> table (n , vector<int> (n , 0));

    for (int i = 0 ; i < 2 * n - 1 ; i ++){
        if (check){
            for (int j = 0 ; j <= i ; j ++){
                int k = i - j;
                if (k < n && k >= 0 && j < n && j >= 0){
                    table[j][k] = count;
                    count ++;
                }
            }
            check = false;
        }

        else if (!check){
            for (int j = 0 ; j <= i ; j ++){
                int k = i - j;
                if (k < n && k >= 0 && j < n && j >= 0){
                    table[k][j] = count;
                    count ++;
                }
            }
            check = true;
        }
    }

    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            cout << table[i][j];
        }
        cout << endl;
    }
}