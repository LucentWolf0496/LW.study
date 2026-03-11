#include <iostream>
using namespace std;

int main() {
    int k;
    cin >> k;
    for (int group = 0; group < k; group++) {
        int m, n;
        cin >> m >> n;
        int **matrix = new int*[m];
        for (int i = 0; i < m; i++) {
            matrix[i] = new int[n];
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> matrix[i][j];
            }
        }
        int sum = 0;
        if (m == 1) {
            for (int j = 0; j < n; j++) {
                sum += *(*(matrix + 0) + j);
            }
        }
        else if (n == 1) {
            for (int i = 0; i < m; i++) {
                sum += *(*(matrix + i) + 0);
            }
        }
        else {
            for (int j = 0; j < n; j++) {
                sum += *(*(matrix + 0) + j);
                sum += *(*(matrix + m - 1) + j);
            }
            for (int i = 1; i < m - 1; i++) {
                sum += *(*(matrix + i) + 0);
                sum += *(*(matrix + i) + n - 1);
            }
        }
        cout << sum << endl;
        for (int i = 0; i < m; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    return 0;
}