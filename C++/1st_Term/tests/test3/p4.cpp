#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool f1(string s){
    for (int i = 0 ; i < s.size() ; i ++){
        if (s[i] >= '0' && s[i] <= '9')
            return true;
    }
    return false;
}

bool f2(string s){
    for (int i = 0 ; i < s.size() ; i ++){
        if (s[i] >= 'a' && s[i] <= 'z')
            return true;
    }
    return false;
}

bool f3(string s){
    for (int i = 0 ; i < s.size() ; i ++){
        if (s[i] >= 'A' && s[i] <= 'Z')
            return true;
    }
    return false;
}

bool f4(string s){
    for (int i = 0 ; i < s.size() ; i ++){
        if (!(s[i] >= '0' && s[i] <= '9') && !(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= 'A' && s[i] <= 'Z'))
            return true;
    }
    return false;
}

int main(){
    int n = 0;
    cin >> n;
    vector<string> list;
    string temp;
    while(cin >> temp){
        list.push_back(temp);
    }
    for (int i = 0 ; i < list.size() ; i ++){
        if (list[i].size() < 6)
            cout << "Not safe" << endl;
        else{
            int count = f1(list[i]) + f2(list[i]) + f3(list[i]) + f4(list[i]);
            if (count == 1)
                cout << "Not safe" << endl;
            else if (count == 2)
                cout << "Medium safe" << endl;
            else
                cout << "Safe" << endl;
        }
    }
    return 0;
}