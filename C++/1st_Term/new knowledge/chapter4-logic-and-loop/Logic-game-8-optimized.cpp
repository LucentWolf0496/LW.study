#include <iostream>
using namespace std;

int main() {
    for (int a = 1; a <= 5; a++) {
        for (int b = 1; b <= 5; b++) {// 如需使用if continue，需要加花括号，因为只有严格连续的for才能省略
            if (b == a) continue;
            for (int c = 1; c <= 5; c++) {
                if (c == a || c == b) continue;
                for (int d = 1; d <= 5; d++) {
                    if (d == a || d == b || d == c) continue;
                    for (int e = 1; e <= 5; e++) {
                        if (e == a || e == b || e == c || e == d) continue;
                        if (e == 2 || e == 3) continue; // E不是第2或第3名

                        // 计算猜测是否正确
                        // 把变量设置成布尔值，更简单地去判断！！！
                        bool gA = (e == 1); // A猜E第1名
                        bool gB = (b == 2); // B猜B第2名
                        bool gC = (a == 5); // C猜A第5名
                        bool gD = (c != 1); // D猜C不是第1名
                        bool gE = (d == 1); // E猜D第1名

                        // 检查条件：第1和第2名的厂猜测正确，其他厂猜测错误
                        // if & continue : 跳过后续内容（自动剔除1，2名不满足于3，4，5名满足的情况）
                        if ((a == 1 || a == 2) && !gA) continue;
                        if ((a != 1 && a != 2) && gA) continue;
                        if ((b == 1 || b == 2) && !gB) continue;
                        if ((b != 1 && b != 2) && gB) continue;
                        if ((c == 1 || c == 2) && !gC) continue;
                        if ((c != 1 && c != 2) && gC) continue;
                        if ((d == 1 || d == 2) && !gD) continue;
                        if ((d != 1 && d != 2) && gD) continue;
                        if ((e == 1 || e == 2) && !gE) continue;
                        if ((e != 1 && e != 2) && gE) continue;

                        // 所有条件满足，输出结果
                        cout << "A: " << a << endl;
                        cout << "B: " << b << endl;
                        cout << "C: " << c << endl;
                        cout << "D: " << d << endl;
                        cout << "E: " << e << endl;
                        return 0;//有答案就直接离场，不需要再设置变量
                    }
                }
            }
        }
    }
    cout << "No answer!" << endl;
    return 0;//这是无答案的终止栏目
}