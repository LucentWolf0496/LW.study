#include <iostream>
#include <set>
#include <cmath>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

int count(int n) {
    if (n <= 1) return 0;
    if (isPrime(n)) return 0;
    int cnt = 0;
    int temp = n;
    if (temp % 2 == 0) {
        ++cnt;
        while (temp % 2 == 0) temp /= 2;
    }
    for (int i = 3; i * i <= temp; i += 2) {
        if (temp % i == 0) {
            ++cnt;
            while (temp % i == 0) temp /= i;
        }
    }
    if (temp > 1) ++cnt;
    return cnt;
}

struct Compare {
    bool operator()(int a, int b) const {
        int fa = count(a);
        int fb = count(b);
        if (fa != fb) return fa < fb;
        return a < b;
    }
};

int main() {
    int num;
    cin >> num;
    multiset<int, Compare> container;
    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < 10; ++j) {
            int x;
            cin >> x;
            container.insert(x);
        }
        auto itLow = container.begin();
        auto itHigh = prev(container.end());
        cout << *itHigh << " " << *itLow << endl;
        container.erase(itLow);
        container.erase(itHigh);
    }
    return 0;
}