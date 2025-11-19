#include <iostream>
#include <vector>
using namespace std;

vector<int> result;
bool check = false;

void get(vector<int> &list , int num , int p){
    if (p == 0){
        check = true;
        for (int i = 0 ; i < num ; i ++){
            for (int j = 0 ; j < result[i] ; j ++){
                if (i == num - 1 && j == result[i] - 1){
                    cout << list[i];
                    break;
                }
                cout << list[i] << " ";
            }
        }
        cout << endl;
        return;
    }
    if (p != 0 && num == list.size()){
        return;
    }
    for (int i = p / list[num] ; i >= 0 ; i --){
        result[num] = i;
        get(list , num + 1 , p - list[num] * i);
    }
}

int main(){
    int n , p;
    cin >> n >> p;
    vector<int> list(n);
    result.resize(n , 0);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    get(list , 0 , p);
    if (!check)
        cout << "NO" << endl;
    return 0;
}