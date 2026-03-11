#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n = 0;
int result = 0;

void dfs(int x , vector<bool> &get , vector<vector<int>> &table){
    if (table[x].empty()){
        get[x] = true;
        result ++;
        return;
    }

    while(!table[x].empty()){
        while (get[table[x][0] - 1]){
            table[x].erase(table[x].begin());
            if (table[x].empty()) break;// fhioisfg iwehfpwqhpofwehfoek[ojfe  ]
        }
        if (table[x].empty()) break;
        dfs(table[x][0] - 1 , get , table);
        table[x].erase(table[x].begin());
    }

    if (table[x].empty()){
        get[x] = true;
        result ++;
        return;
    }
}

int main(){
    cin >> n;
    vector<bool> get(n , false);
    vector<vector<int>> table(n , vector<int>());
    for (int i = 0 ; i < n ; i ++){
        int k = 0;
        cin >> k;
        if (k == 0) continue;
        else{
            for (int j = 0 ; j < k ; j ++){
                int temp;
                cin >> temp;
                table[i].push_back(temp);
            }
        }
    }
    dfs(0 , get , table);
    cout << result;
}