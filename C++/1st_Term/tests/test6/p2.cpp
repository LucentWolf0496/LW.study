#include <iostream>
#include <vector>
using namespace std;

int main(){
    int m , n;
    cin >> m >> n;
    vector<int> list(m);
    for (int i = 0 ; i < m ; i ++){
        cin >> list[i]; 
    }
    int temp = 0;
    int result = 0;
    for (int i = 0 ; i < m - 1 ; i ++){
        temp += list[i];
        if (temp <= n && temp + list[i + 1] > n){
            result ++;
            temp = 0;
        }
    }
    cout << result + 1;
}