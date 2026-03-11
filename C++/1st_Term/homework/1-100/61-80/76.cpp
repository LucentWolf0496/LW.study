#include <string>
#include <iostream>
using namespace std;

void test(string x , string y){
    int a = x.size();
    int b = y.size();
    for (int i = 0 ; i < a - b + 1 ; i ++){
        bool check = true;
        for (int j = 0 ; j < b ; j ++){
            if (x[i + j] != y[j])
                check = false;
        }
        if (check){
            cout << y << " is substring of " << x << endl;
            return;
        }
    }
    cout << "No substring" << endl;
    return;
}

int main(){
    string s1 , s2;
    getline(cin , s1);
    getline(cin , s2);
    if (s1.size() >= s2.size())
        test(s1 , s2);
    else
        test(s2 , s1);
}