#include <iostream>
#include <vector>
using namespace std;

int main(){
    int a , b;
    cin >> a >> b;
    vector<int> list;
    for (int i = 0 ; i < a ; i ++){
        int temp;
        cin >> temp;
        list.push_back(temp);
    }
    int sum = 0;
    for (int i = 0 ; i < a - b + 1 ; i ++){
        int temp = 0;
        for (int j = i ; j < i + b ; j ++){
            temp += list[j];
        }
        if (temp > sum)
            sum = temp;
    }
    cout << sum << endl;
}