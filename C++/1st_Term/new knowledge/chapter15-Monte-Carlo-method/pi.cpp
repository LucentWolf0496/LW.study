#include <iostream>
#include <random>// 随机数与蒙特卡洛法初识

double estimate_pi(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    int inside_circle = 0;
    for (int i = 0; i < n; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        if (x*x + y*y <= 1.0) {
            inside_circle++;
        }
    }
    return 4.0 * inside_circle / n;
}

int main() {
    double pi_estimate = estimate_pi(33550336);// ......
    std::cout << "Estimated Pi: " << pi_estimate << std::endl;
    return 0;
}