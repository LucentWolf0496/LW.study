//this is an optimized version of finding the students who went to Tsinghua University.
#include <iostream>
using namespace std;

int main()
{
    int cc1, cc2, cc3, cc4, cc5, cc6; // 定义6个变量，分别表示6句话
    int A, B, C, D, E, F; // 定义6个变量，分别表示6个人
    
    for (int i = 0; i < 64; i++)
    {
        A = (i & 32) >> 5; // 从i中经位操作分离出A
        B = (i & 16) >> 4; // 从i中经位操作分离出B
        C = (i & 8) >> 3;  // 从i中经位操作分离出C
        D = (i & 4) >> 2;  // 从i中经位操作分离出D
        E = (i & 2) >> 1;  // 从i中经位操作分离出E
        F = i & 1;         // 从i中经位操作分离出F
        
        cc1 = A || B; // 第1句话的逻辑表达式
        cc2 = !(A && D); // 第2句话的逻辑表达式
        cc3 = (A && E) || (A && F) || (E && F); // 第3句话的逻辑表达式
        cc4 = (B && C) || (!B && !C); // 第4句话的逻辑表达式
        cc5 = (C && !D) || (D && !C); // 第5句话的逻辑表达式
        cc6 = D || (!D && !E); // 第6句话的逻辑表达式
        
        // 测试6句话都为真时，才输出谁是罪犯
        if (cc1 + cc2 + cc3 + cc4 + cc5 + cc6 == 6)
        {
            // 输出判断结果
            cout << "A: " << (A == 0 ? "不是" : "是") << "罪犯" << endl;
            cout << "B: " << (B == 0 ? "不是" : "是") << "罪犯" << endl;
            cout << "C: " << (C == 0 ? "不是" : "是") << "罪犯" << endl;
            cout << "D: " << (D == 0 ? "不是" : "是") << "罪犯" << endl;
            cout << "E: " << (E == 0 ? "不是" : "是") << "罪犯" << endl;
            cout << "F: " << (F == 0 ? "不是" : "是") << "罪犯" << endl;
            cout << "-------------------" << endl;
        }
    }
    
    return 0;
}