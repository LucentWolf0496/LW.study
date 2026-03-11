#include <iostream>
using namespace std;

int main(){
    int a , b = 0;
    cin >> a >> b;
    cout << a << "+" << b << "=" << a + b << endl;
    cout << a << "-" << b << "=" << a - b << endl;
    cout << a << "*" << b << "=" << a * b << endl;
    if (b != 0)
        cout << a << "/" << b << "=" << a / b << endl;
    else
        cout << a << "/" << b << "=" << "error" << endl;
}