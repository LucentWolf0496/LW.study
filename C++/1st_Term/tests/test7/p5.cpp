#include <iostream>
#include <string>
using namespace std;

void f(string s){
    bool check1 = true;
    bool check0 = true;
    for (int i = 0 ; i < s.size() ; i ++){
        if (s[i] == '0') check1 = false;
        if (s[i] == '1') check0 = false;
    }
    if (check0){
        cout << "A";
        return;
    }
    if (check1){
        cout << "B";
        return;
    }
    cout << "C";
    int n = s.size();
    string s1 = s.substr(0 , n / 2);
    string s2 = s.substr(n / 2);
    f(s1);
    f(s2);
}

int main(){
    string s;
    cin >> s;
    f(s);
}