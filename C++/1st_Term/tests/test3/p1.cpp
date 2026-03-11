#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    int x = 0;
    cin >> s >> x;
    if (s == "heitao" && x >= 2 && x <= 9)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
    return 0;
}