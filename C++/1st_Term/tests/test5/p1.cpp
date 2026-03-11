#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    int m = 0;
    cin >> m;
    double result;
    double x = 240 * 0.4883;
    double y = x + 160 * 0.5383;
    if (m <= x)
        result = m / 0.4883;
    else if (m > x && m <= y)
        result = 240 + (m - x) / 0.5383;
    else
        result = 400 + (m - y) / 0.7883;
    cout << fixed << setprecision(2) << result;
}