//example 5
#include <iostream>
using namespace std;

int main()
{
    int cc1 = 0, cc2 = 0, cc3 = 0, cc4 = 0, cc5 = 0;
    int bb1 = 0, bb2 = 0, bb3 = 0;
    for (int ch = 1; ch <= 3; ch ++)
        for (int ma = 1; ma <= 3; ma ++)
            for (int po = 1; po <= 3; po ++)
                for (int ge = 1; ge <= 3; ge ++)
                    for (int mu = 1; mu <= 3; mu ++)
                        for (int ar = 1; ar <= 3; ar ++)
                        {
                            cc1 = (po != ma);
                            cc2 = (ge != ch);
                            cc3 = (ge != 2);
                            cc4 = (ge != 1) && (ma != 1) && (ge != ma);
                            cc5 = (mu != 2) && (ch != 2) && (mu != ch);
                            bb1 = (ch == 1) + (ma == 1) + (po == 1) + (ge == 1) + (mu == 1) + (ar == 1);
                            bb2 = (ch == 2) + (ma == 2) + (po == 2) + (ge == 2) + (mu == 2) + (ar == 2);
                            bb3 = (ch == 3) + (ma == 3) + (po == 3) + (ge == 3) + (mu == 3) + (ar == 3);
                            if (cc1 == 1 && cc2 == 1 && cc3 == 1 && cc4 == 1 && cc5 == 1)
                            {
                                if (bb1 == 2 && bb2 == 2 && bb3 == 2)
                                {// 模板：更高效的规范输出模式：cout <<（表达式1 ？“  ” ： “  ”）
                                 // 原理：判断表达式1（记得用==），是真就执行？后输出，假则执行：后输出
                                 // 简便，清晰，规范！
                                cout << "A teaches: "
                                     << (ch == 1 ? "ch " : "")
                                     << (ma == 1 ? "ma " : "")
                                     << (po == 1 ? "po " : "")
                                     << (ge == 1 ? "ge " : "")
                                     << (mu == 1 ? "mu " : "")
                                     << (ar == 1 ? "ar " : "")
                                     << endl;

                                cout << "B teaches: "
                                     << (ch == 2 ? "ch " : "")
                                     << (ma == 2 ? "ma " : "")
                                     << (po == 2 ? "po " : "")
                                     << (ge == 2 ? "ge " : "")
                                     << (mu == 2 ? "mu " : "")
                                     << (ar == 2 ? "ar " : "")
                                     << endl;

                                cout << "C teaches: "
                                     << (ch == 3 ? "ch " : "")
                                     << (ma == 3 ? "ma " : "")
                                     << (po == 3 ? "po " : "")
                                     << (ge == 3 ? "ge " : "")
                                     << (mu == 3 ? "mu " : "")
                                     << (ar == 3 ? "ar " : "")
                                     << endl;
                                return 0;
                                }
                            }
                        }
    return 0;
}