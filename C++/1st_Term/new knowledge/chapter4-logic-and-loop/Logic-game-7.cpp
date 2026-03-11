//example 5
#include <iostream>
using namespace std;

int main()
{
    int cc1 = 0, cc2 = 0, cc3 = 0, cc4 = 0, cc5 = 0;
    int bb1 = 0, bb2 = 0, bb3 = 0;
    int thu = 0;
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
                                {
                                cout << "ch is " << char('A' - 1 + ch) << endl;
                                cout << "ma is " << char('A' - 1 + ma) << endl;
                                cout << "po is " << char('A' - 1 + po) << endl;
                                cout << "ge is " << char('A' - 1 + ge) << endl;
                                cout << "mu is " << char('A' - 1 + mu) << endl;
                                cout << "ar is " << char('A' - 1 + ar) << endl;
                                thu = 1;
                                }
                            }
                        }
    if (thu == 0)
        cout << "No answer!" << endl;
}