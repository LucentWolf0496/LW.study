#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<vector<int>> table(n , vector<int>(2));
    vector<bool> check(100001 , false);
    for (int i = 0 ; i < n ; i ++){
        cin >> table[i][0] >> table[i][1];
    }
    for (int i = 0 ; i < n ; i ++){
        check[table[i][0]] = true;
    }
    for (int i = 0 ; i < n ; i ++){
        check[table[i][1]] = false;
    }
    int count = 0;
    vector<int> list;
    for (int i = 0 ; i < 100001 ; i ++){
        if (check[i]){
            count ++;
            list.push_back(i);
        }
    }
    if (count == 0)
        cout << "None" << endl;
    else{
        cout << list[0];
        for (int i = 1 ; i < list.size() ; i ++){
            cout << ", " << list[i];
        }
    }
}