#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

static bool compare(vector<int> &x , vector<int> &y){
    return x[2] < y[2];
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> table(n , vector<int>(3));
    for (int i = 0 ; i < n ; i ++){
        cin >> table[i][0] >> table[i][1];
        table[i][2] = table[i][0] - table[i][1];
    }
    sort(table.begin() , table.end() , compare);
    int result = 0;
    for (int i = 0 ; i < n / 2 ; i ++){
        result += table[i][0];
    }
    for (int i = n / 2 ; i < n ; i ++){
        result += table[i][1];
    }
    cout << result;
}