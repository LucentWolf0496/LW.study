#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        
        vector<int> monkeys;
        for (int i = 1; i <= n; i++) {
            monkeys.push_back(i);
        }
        
        int current = 0;
        while (monkeys.size() > 1) {
            current = (current + m - 1) % monkeys.size();
            monkeys.erase(monkeys.begin() + current);
        }
        
        cout << monkeys[0] << endl;
    }
    return 0;
}