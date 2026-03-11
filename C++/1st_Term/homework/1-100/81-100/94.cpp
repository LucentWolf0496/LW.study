#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<vector<int>> table(n , vector<int>(n));
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            cin >> table[i][j];
        }
    }
    int temp1 = 0;
    int temp2 = 0;
    int temp3 = 0;
    int temp4 = 0;
    int sum = 0;
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            for (int k = i ; k < n ; k ++){
                for (int l = j ; l < n ; l ++){
                    int temp = 0;
                    for (int row = i ; row <= k ; row ++){
                        for (int line = j ; line <= l ; line ++){
                            temp += table[row][line];
                        }
                    }
                    if (temp > sum){
                        sum = temp;
                        temp1 = i;
                        temp2 = k;
                        temp3 = j;
                        temp4 = l;
                    }
                }
            }
        }
    }
    for (int i = temp1 ; i <= temp2 ; i ++){
        cout << table[i][temp3];
        for (int j = temp3 + 1 ; j <= temp4 ; j ++){
            cout << " " << table[i][j];
        }
        cout << endl;
    }
    cout << sum << endl;
}