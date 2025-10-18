#include <iostream>
using namespace std;

int last[1010];// 记录余数出现的位置，索引是余数值，数组值是该余数值出现的位置

int main() {
    int a, b;
    cin >> a >> b;
    int remainder = a % b;
    
    for (int i = 1; ; i++) {
        if (remainder == 0) {
            cout << 0 << endl;
            break;
        }
        
        if (last[remainder] == 0) {
            last[remainder] = i;
        } else {
            cout << i - last[remainder] << endl;
            break;
        }
        
        remainder = (remainder * 10) % b;// 余数超过一位数也是没事的，只要达成循环就行
    }
    
    return 0;
}