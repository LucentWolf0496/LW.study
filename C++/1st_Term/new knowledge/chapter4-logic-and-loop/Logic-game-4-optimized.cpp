#include <iostream>
using namespace std;

int main() {
    for (int best = 1; best <= 4; best++) {
        bool correctA = (best == 2);
        bool correctB = (best == 4);
        bool correctC = (best != 3);
        bool correctD = (best != 4); // D说B说错了，因此如果B错了，D就对了

        int count = correctA + correctB + correctC + correctD;
        if (count == 1) {
            cout << "最佳车号: " << best << endl;
            if (correctA) cout << "说对的专家: A" << endl;
            if (correctB) cout << "说对的专家: B" << endl;
            if (correctC) cout << "说对的专家: C" << endl;
            if (correctD) cout << "说对的专家: D" << endl;
            break;
        }
    }
    return 0;
}