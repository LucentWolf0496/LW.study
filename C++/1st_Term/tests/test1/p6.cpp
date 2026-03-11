#include <iostream>
#include <string>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    for (int x = 0 ; x < n ; x ++){
        string s;
        cin >> s;
        bool check = true;
        for (int i = 0 ; i < s.size() - 1 ; i ++){
            if (s[i] == s[i + 1] && s[i] != '?' && s[i + 1] != '?')
                check = false;
        }
        if (check)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}