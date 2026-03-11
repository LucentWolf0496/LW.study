#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<float> list(5);
    int result = 0;
    for (int i = 0 ; i < 5 ; i ++){
        cin >> list[i];
        if (list[i] > 18 && list[i] <= 20) result ++;
    }
    if (result >= 3) cout << "Yes";
    else cout << "No";
}