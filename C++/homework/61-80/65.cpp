#include <iostream>
#include <string>
using namespace std;

int main(){
    string s1 , s2;
    getline (cin , s1);
    s2 = s1;
    for (int i = 0 ; i < s1.size() - 1 ; i ++){
        s1[i] = s2[i] + s2[i + 1];
    }
    s1[s1.size() - 1] = s2[s1.size() - 1] + s2[0];
    cout << s1 << endl;
}