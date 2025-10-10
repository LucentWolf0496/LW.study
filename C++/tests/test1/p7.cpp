#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool compare(string x , string y){
    string temp1 = x + y;
    string temp2 = y + x;
    for (int i = 0 ; i < temp1.size() ; i ++){
        if (temp1[i] == temp2[i]) continue;
        if (temp1[i] > temp2[i])
            return false;
        else if (temp1[i] < temp2[i])
            return true;
    }
}

int main(){
    int n = 0;
    cin >> n;
    vector<string> list;
    for (int x = 0 ; x < n ; x ++){
        string s;
        cin >> s;
        list.push_back(s);
    }
    for (int i = 1 ; i < list.size() ; i ++){
        for (int j = 0 ; j < list.size() - i ; j ++){
            if (compare(list[j] , list[j + 1])){
                string temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
    for (int i = 0 ; i < list.size() ; i ++){
        cout << list[i];
    }
    cout << endl;
}