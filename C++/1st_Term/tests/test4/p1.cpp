#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    long a = 0;
    cin >> a;
    if (a == 0){
        cout << 1 << endl;
        return 0;
    }
    int count = 0;
    while(a > 0){
        count ++;
        a /= 10;
    }
    cout << count << endl;
    return 0;
}
