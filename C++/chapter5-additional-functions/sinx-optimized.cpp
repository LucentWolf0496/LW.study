#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float x, y;
    cin >> x >> y; // x为角度值，y为精度要求

    // 先将x映射到[-π, π]区间内，以提高计算效率
    const float PI = 3.14159265358979323846;
    x = fmod(x, 2 * PI); // 取模缩小范围
    if (x > PI) {
        x -= 2 * PI;
    } else if (x < -PI) {
        x += 2 * PI;
    }

    float sum = 0.0;
    float term = x; // 第一项：x^1/1!
    int n = 0;
    while (fabs(term) >= y) {
        sum += term;
        n++;
        // 递推计算下一项：term * (-x^2) / ((2*n) * (2*n+1))
        term = term * (-x * x) / ((2 * n) * (2 * n + 1));
    }
    cout << sum << endl;
    return 0;
}