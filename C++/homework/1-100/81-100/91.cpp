#include <iostream>
#include <vector>
using namespace std;

bool check = false;

void get(int t , vector<int> list , int result){
    if (check || list.empty())
        return;
    if (result == t){
        check = true;
        return;
    }
    for (int i = 0 ; i < list.size() ; i ++){
        result *= list[i];
        vector<int> temp = list;
        list.erase(list.begin() + i);
        get(t , list , result);
        list = temp;
        result /= list[i];
    }
    
}

int main(){
    int t , n;
    cin >> t >> n;
    vector<int> list;
    list.resize(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    bool check0 = false;
    for (int i = 0 ; i < list.size() ; i ++){
        if (list[i] == 0){// 小心集合中的0导致的除0报错，应将0去除
            list.erase(list.begin() + i);
            i --;
            check0 = true;
        }
    }
    if (check0 && t == 0){
        cout << "YES" << endl;
        return 0;
    }
    for (int i = 0 ; i < list.size() ; i ++){
        if (t % list[i] != 0){
            list.erase(list.begin() + i);
            i --;
        }
    }
    get(t , list , 1);
    if (check)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}