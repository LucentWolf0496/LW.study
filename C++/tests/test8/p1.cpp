#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int a , b;
    cin >> a >> b;
    int c = 0;
    int d = 0;
    c = a / b;
    d = a % b;
    c = c + d;
    if (a % c == 0) cout << "YES";
    else cout << "NO";
}