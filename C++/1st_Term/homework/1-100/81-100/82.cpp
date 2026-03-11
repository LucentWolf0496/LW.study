#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main(){
    string s , s1 , s2;
    cin >> s;
    for (int i = 0 ; i < s.size() ; i ++){
        if (s[i] == ',')
            s[i] = ' ';
    }
    stringstream ss(s);
    ss >> s >> s1 >> s2;

    vector<int> s11;
    vector<int> s22;

    for (int i = 0 ; i < s.size() ; i ++){
        bool check1 = true;
        for (int j = 0 ; j < s1.size() ; j ++){
            if (i + j < s.size()){
                if (s[i + j] != s1[j])
                    check1 = false;
            }
            else
                check1 = false;
        }
        if(check1)
            s11.push_back(i + s1.size() - 1);
    }

    for (int i = 0 ; i < s.size() ; i ++){
        bool check2 = true;
        for (int j = 0 ; j < s2.size() ; j ++){
            if (i + j < s.size()){
                if (s[i + j] != s2[j])
                    check2 = false;
            }
            else
                check2 = false;
        }
        if(check2)
            s22.push_back(i);
    }

    if (s11.empty() || s22.empty() || s22[s22.size() - 1] - s11[0] <= 0)
        cout << -1 << endl;
    else
        cout << s22[s22.size() - 1] - s11[0] - 1 << endl;
}