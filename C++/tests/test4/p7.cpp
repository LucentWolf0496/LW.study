#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int a , b;
    cin >> a >> b;
    if (a == b){
        cout << 0 << endl;
        return 0;
    }
    else if (a > b){
        cout << a - b << endl;
    }
    else{
        int count = 0;
        while(a * 2 <= b){
            count ++;
            a = a * 2;
        }
        int p = b - a;
        int q = a * 2 - b + 1;
        count += (p > q ? q : p);
        cout << count << endl;
    }
    return 0;
}