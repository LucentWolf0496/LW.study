#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

int main(){
    int meat , pot;
    cin >> meat >> pot;
    vector<int> list;
    int sum = 0;
    for (int i = 0 ; i < meat ; i ++){
        int temp;
        cin >> temp;
        sum += temp;
        list.push_back(temp);
    }
    sort(list.begin() , list.end());
    reverse(list.begin() , list.end());
    double time = 0;
    while(list[0] * pot > sum && pot >= 2){
        sum -= list[0];
        list.erase(list.begin());
        pot --;
    }
    time = sum / (pot + 0.0);
    cout << fixed << setprecision(3) << time;
}