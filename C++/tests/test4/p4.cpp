#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<long long> length(n);
    vector<long long> label(n);
    vector<long long> thu(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> length[i] >> label[i];
    }
    long long result = 0;
    for (int i = 0 ; i < n ; i ++){
        thu[i] = max(label[i] , length[i] - label[i]);
    }
    sort(thu.begin() , thu.end());
    reverse(thu.begin() , thu.end());
    if (n == 1)
        cout << length[0] << endl;
    else{
        sort(length.begin() , length.end());
        reverse(length.begin() , length.end());
        cout << (thu[0] + thu[1] > length[0] ? thu[0] + thu[1] : length[0]) << endl;
    }
    return 0;
}