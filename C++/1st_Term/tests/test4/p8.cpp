#include <iostream>
using namespace std;

int main(){
    int x = 1;
    int y = 1;
    int z = 2;
    int n = 0;
    cin >> n;
    if (n == 1)
        cout << 1 << endl;
    else if (n == 2)
        cout << 2 << endl;
    else{
        for (int i = 0 ; i < n - 2 ; i ++){
            int tx = x;
            int ty = y;
            int tz = z;
            x = ty;
            y = tz;
            z = tx + tz * 2;
            if (z >= 10000)
                z %= 10000;
        }
        cout << z << endl;
    }
    return 0;
}