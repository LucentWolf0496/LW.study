#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int f(int x , vector<int> list){
    int left = 0 , right = 0;
    for (int i = 0 ; i < x ; i ++){
        if (list[i] > left)
            left = list[i];
    }
    for (int i = x + 1 ; i < list.size() ; i ++){
        if (list[i] > right)
            right = list[i];
    }
    if (list[x] >= left || list[x] >= right)
        return 0;
    else{
        int count = 0;
        (left > right ? count = right - list[x] : count = left - list[x]);
        return count;
    }
}

int main(){
    int temp;
    vector<int> list;
    while(cin >> temp){
        list.push_back(temp);
    }
    int n = list.size();
    int count = 0;
    for (int i = 1 ; i < n - 1 ; i ++){
        count += f(i , list);
    }
    cout << count << endl;
    return 0;
}