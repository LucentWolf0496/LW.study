#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> senders(n);
    vector<vector<int>> mentions(n);
    for (int i = 0; i < n; i++) {
        int a, k;
        cin >> a >> k;
        senders[i] = a;
        vector<int> ment(k);
        for (int j = 0; j < k; j++) {
            cin >> ment[j];
        }
        mentions[i] = ment;
    }
    vector<int> count(100, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < mentions[i].size(); j++) {
            int user = mentions[i][j];
            if (user >= 1 && user < 100) {
                count[user]++;
            }
        }
    }
    int maxCount = 0;
    int focusUser = 0;
    for (int i = 1; i < 100; i++) {
        if (count[i] > maxCount) {
            maxCount = count[i];
            focusUser = i;
        }
    }
    vector<bool> mentionedBy(100, false);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < mentions[i].size(); j++) {
            if (mentions[i][j] == focusUser) {
                mentionedBy[senders[i]] = true;
                break;
            }
        }
    }
    cout << focusUser << endl;
    bool first = true;
    for (int i = 1; i < 100; i++) {
        if (mentionedBy[i]) {
            if (first) {
                cout << i;
                first = false;
            } else {
                cout << " " << i;
            }
        }
    }
    cout << endl;
    return 0;
}