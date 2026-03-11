#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;

int main(){
    string s;
    getline(cin , s);
    int count = 0;
    vector<string> list;

    stringstream ss1(s);
    string temp;
    while (ss1 >> temp){
        list.push_back(temp);
    }

    for (int i = 0 ; i < s.size() ; i ++){
        if (s[i] == ' '){
            count ++;
        }
    }

    int size = list.size();
    if (size == 1){
        cout << list[0];
        for (int i = 0 ; i < count ; i ++){
            cout << ' ';
        }
        cout << endl;
        return 0;
    }
    int num1 = count / (size - 1);
    int num2 = count % (size - 1);
    for (int i = 0 ; i < size - 1 ; i ++){
        cout << list[i];
        for (int j = 0 ; j < num1 ; j ++){
            cout << ' ';
        }
    }
    cout << list[size - 1];
    for (int i = 0 ; i < num2 ; i ++){
        cout << ' ';
    }
    cout << endl;
    return 0;
}