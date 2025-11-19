#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    if (n == 1){
        cout << 10 << endl;
        return 0;
    }

    int x = 1 , y = 1 , z = 1 , w = 1;
    for (int i = 1 ; i < n ; i ++){
        int tempx = x , tempy = y , tempz = z , tempw = w;
        x = tempy + tempz;
        y = tempx * 2;
        z = tempx * 2 + tempw;
        w = tempz * 2;
    }
    int sum = x * 4 + y * 2 + z * 2 + w;
    cout << sum << endl;
    
    return 0;
}