#include <iostream>
using namespace std;

int main(){
    float i = 1.0;
    float a = 0.0;
    cin >> a;
    for (int x = 1 ; x < 100000 ; x ++){
        i = (i + a / (i + 0.0)) / 2.0;
    }
    cout << i;
}