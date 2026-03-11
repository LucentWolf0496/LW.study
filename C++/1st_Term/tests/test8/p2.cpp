#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> list(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    sort(list.begin() , list.end());
    int mid = 0;
    int mid1 = 0;
    if ((list[0] + list[n - 1]) % 2 == 0){
        mid = (list[0] + list[n - 1]) / 2;
        mid1 = mid;
    }
    else{
        mid = (list[0] + list[n - 1]) / 2;
        mid1 = mid + 1;
    }
    for (int i = 0 ; i < n ; i ++){
        if (list[i] == mid || list[i] == mid1){
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
}