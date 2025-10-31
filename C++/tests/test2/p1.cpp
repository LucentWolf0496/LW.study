#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct per{
    string name;
    float temp;
    int cough;
};

int main(){
    int n = 0;
    int count = 0;
    cin >> n;
    vector<per> list;
    for (int i = 0 ; i < n ; i ++){
        per h;
        cin >> h.name >> h.temp >> h.cough;
        list.push_back(h);
    }
    for (int i = 0 ; i < n ; i ++){
        if (list[i].temp >= 37.5 && list[i].cough == 1){
            count ++;
            cout << list[i].name << endl;
        }
    }
    cout << count << endl;
    return 0;
}