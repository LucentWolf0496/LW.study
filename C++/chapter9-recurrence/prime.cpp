#include <iostream>
#include <vector>
using namespace std;

bool isprime(int n){
    for (int i = 2 ; i * i <= n ; i ++){
        if (n % i == 0)
            return false;
    }
    return true;
}

int main(){
    int n = 0;
    cin >> n;
    vector<int> prime;
    for (int i = 2 ; i * i <= n ; i ++){
        if (isprime(i)){
            prime.push_back(i);
        }
    }
    for (int i = 0 ; i < prime.size() ; i ++){
        if (n % prime[i] == 0){
            cout << n / prime[i] << endl;
            return 0;
        }
    }
}