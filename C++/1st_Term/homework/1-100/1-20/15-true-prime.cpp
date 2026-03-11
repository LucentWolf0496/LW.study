#include <iostream>
#include <vector>
using namespace std;

int f(int x){
    if (10000 <= x && x <= 99999){
        int a = x / 10000;
        x %= 10000;
        int b = x / 1000;
        x %= 1000;
        int c = x / 100;
        x %= 100;
        int d = x / 10;
        x %= 10;
        int e = x;
        int sum = 10000 * e + 1000 * d + 100 * c + 10 * b + a;
        return sum;
    }
    if (1000 <= x && x <= 9999){
        int b = x / 1000;
        x %= 1000;
        int c = x / 100;
        x %= 100;
        int d = x / 10;
        x %= 10;
        int e = x;
        int sum =1000 * e + 100 * d + 10 * c + b;
        return sum;
    }
    if (100 <= x && x <= 999){
        int c = x / 100;
        x %= 100;
        int d = x / 10;
        x %= 10;
        int e = x;
        int sum = 100 * e + 10 * d + c;
        return sum;
    }
    if (10 <= x && x <= 99){
        int d = x / 10;
        x %= 10;
        int e = x;
        int sum = 10 * e + d;
        return sum;
    }
    if (1 <= x && x <= 9){
        return x;
    }
}

bool isprime(int x){
    if (x == 1)
        return false;
    for (int i = 2 ; i * i <= x ; i ++){
        if (x % i == 0){
            return false;
            break;
        }
    }
    return true;
}

int main(){
    vector<int> result;
    int m = 0 , n = 0;
    cin >> m >> n;
    for (int x = m ; x <= n ; x ++){
        if (isprime(x) && isprime(f(x)))
            result.push_back(x);
    }
    if (result.size() == 0){// 审题，记得对没有真素数也就是size=0的情况标记好No
        cout << "No" << endl;
        return 0;
    }
    cout << result[0];
    for (int i = 1 ; i < result.size() ; i ++){
        cout << "," << result[i];
    }
    cout << endl;
    return 0;
}