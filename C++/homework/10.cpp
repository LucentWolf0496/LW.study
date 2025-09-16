#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    for (int a = 2; a <= n; a++) {
        int a_cubed = pow(a, 3);// 将a x y的立方移出最内层循环简化运算防止超时
        
        for (int x = 2; x <= a; x++) {
            int x_cubed = pow(x, 3);
            
            for (int y = x; y <= a; y++) {
                int y_cubed = pow(y, 3);
                
                for (int z = y; z <= a; z++) {
                    if (a_cubed == x_cubed + y_cubed + pow(z, 3)) {
                        cout << "Cube = " << a << ", Triple = (" << x << "," << y << "," << z << ")\n";
                    }
                }
            }
        }
    }
    
    return 0;
}