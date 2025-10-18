#include <iostream>
#include <vector>
using namespace std;

vector<int> queens; // 存储每行皇后的列位置，利用了结论：必然在不同行，简化判别与算法
int solutions = 0;// 只用管列即可，反正行必然不一样

bool isSafe(int row, int col) {// 再分出判别模块，简化代码结构，易于阅读、维护与管理
    for (int i = 0; i < row; i++) {
        if (queens[i] == col || abs(queens[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

void solve(int row, int n) {
    if (row == n) {
        // 打印解
        for (int i = 0; i < n; i++) {
            cout << i+1 << "-" << queens[i]+1 << endl;
        }
        cout << endl;
        solutions++;
        return;// 关键点，回溯到solve(row + 1, n)这句代码之后，继续col++，继续求解
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {// 模块化的好处
            queens[row] = col;// 由于逐步回溯，vector被“覆盖式写入”，不需清理vector
            solve(row + 1, n);// 执行完有解之后回溯到这一步之后，达成有解之回溯
        }
    }// 最关键：void执行完也会自动回溯到调用点之后！！！达成了无解情况的回溯
}// 有解无解，均会遍历回溯

int main() {
    int n = 8;
    queens.resize(n);// 初始化数组，预留空间，而非一个一个push_back导入数据，契合DFS的工作流
    solve(0, n);
    cout << "Total solutions: " << solutions << endl;
    return 0;
}