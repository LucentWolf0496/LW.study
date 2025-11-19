#include <iostream>
using namespace std;

int get(int m , int n){
    if (n == 1 || m == 0)
        return 1;
    if (m < n)
        return get(m , n - 1);
    else{
        return get(m - n , n) + get(m , n - 1);
    }
}

int main(){
    int i = 0;
    cin >> i;
    for (int j = 0 ; j < i ; j ++){
        int m , n;
        cin >> m >> n;
        cout << get(m , n) << endl;
    }
    return 0;
}