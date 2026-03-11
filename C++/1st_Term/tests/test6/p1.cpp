#include <iostream>
#include <string>
using namespace std;

int main(){
    int n;
    string s;
    cin >> n;
    cin >> s;
    int result = 0;
    for (int i = 0 ; i < n ; i ++){
        if (s[i] == 'A') result += 5;
        else if (s[i] == 'B') result += 7;
        else if (s[i] == 'C') result += 25;
    }
    cout << result << endl;
}