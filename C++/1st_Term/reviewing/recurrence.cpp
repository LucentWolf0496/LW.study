#include <iostream>
#include <vector>
using namespace std;

int price;
vector<int> list;
vector<int> result;
bool check = false;

void dfs(int num , int index , int money){
    if (money > price) return;
    if (money == price){
        check = true;
        cout << result[0];
        for (int i = 1 ; i < num ; i ++){
            cout << " " << result[i];
        }
        cout << endl;
        return;
    }
    for (int i = index ; i < list.size() ; i ++){
        result.push_back(list[i]);
        dfs(num + 1 , i , money + list[i]);
        result.pop_back();
    }
}

int main(){
    int m;
    cin >> m >> price;
    list.resize(m);
    for (int i = 0 ; i < m ; i ++){
        cin >> list[i];
    }
    dfs(0 , 0 , 0);
    if (!check) cout << "NO" << endl;
    return 0;
}
