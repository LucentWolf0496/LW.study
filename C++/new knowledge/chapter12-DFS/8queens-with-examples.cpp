#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> colone(8);
int count = 0;

bool safe(int m , int n){// m列n行
    for (int i = 0 ; i < n ; i ++){// colone[i]列i行
        if (m == colone[i] || abs(m - colone[i]) == abs(n - i))
            return false;
    }
    return true;
}

void get(int n , int col){
    if (col == 8){
        count ++;
        cout << count << endl;
        vector<vector<string>> table(8 , vector<string>(8 , "狮"));
        for (int i = 0 ; i < 8 ; i ++){
            table[i][colone[i]] = "猫";
        }
        for (int i = 0 ; i < 8 ; i ++){
            cout << table[i][0];
            for (int j = 1 ; j < 8 ; j ++){
                cout << " " << table[i][j];
            }
            cout << endl;
        }
        return;
    }
    for (int i = 0 ; i < 8 ; i ++){
        if (safe(i , col)){
            colone[col] = i;
            get(n , col + 1);
        }
    }
}

int main(){
    get(8 , 0);
    return 0;
}