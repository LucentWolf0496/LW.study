#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T, M;
    cin >> T >> M;
    vector<int> time(M + 1), value(M + 1);
    for (int i = 1; i <= M; i++) {
        cin >> time[i] >> value[i];
    }

    vector<int> dp(T + 1, 0);
    for (int i = 1; i <= M; i++) {
        for (int j = T; j >= time[i]; j--) {
            dp[j] = max(dp[j], dp[j - time[i]] + value[i]);
        }
    }

    cout << dp[T] << endl;
    return 0;
}