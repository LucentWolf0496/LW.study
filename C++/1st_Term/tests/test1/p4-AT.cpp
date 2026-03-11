#include <iostream>
#include <vector>
using namespace std;

int main(){
    int temp;
    vector<int> list;
    while(cin >> temp){
        list.push_back(temp);
    }
    vector<int> left;
    vector<int> right;
    int x = list[0] , y = list[list.size() - 1];
    for (int i = 0 ; i < list.size() ; i ++){
        left.push_back(x);
        if (list[i] > x)
            x = list[i];
    }
    for (int i = list.size() - 1 ; i >= 0 ; i --){
        right.push_back(y);
        if (list[i] > y)
            y = list[i];
    }
    int count = 0;
    for (int i = 0 ; i < list.size() ; i ++){
        if (list[i] < left[i] && list[i] < right[list.size() - 1 - i]){
            (left[i] < right[list.size() - 1 - i] ? count += left[i] - list[i] : count += right[list.size() - 1 - i] - list[i]);
        }
    }
    cout << count << endl;
    return 0;
}