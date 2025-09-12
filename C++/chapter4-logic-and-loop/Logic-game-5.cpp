//example 5
#include <iostream>
using namespace std;

int main()
{
    int a = 0, b = 0, c = 0, d = 0, e = 0;
    int A = 0, B = 0, C = 0, D = 0, E = 0;
    int thu = 0;
    for (a = 1; a <= 5; a++)
        for (b = 1; b <= 5; b++)
            for (c = 1; c <= 5; c++)
                for (d = 1; d <= 5; d++)
                    for (e = 1; e <= 5; e++)
                        if (a != b && a != c && a != d && a != e && b != c && b != d && b != e && c != d && c != e && d != e)
                        {
                            A = (b == 2) + (a == 3);
                            B = (b == 2) + (e == 4);
                            C = (c == 1) + (d == 2);
                            D = (c == 5) + (d == 3);
                            E = (e == 4) + (a == 1);
                            if (A == 1 && B == 1 && C == 1 && D == 1 && E == 1)
                            {
                                cout << "A ranking " << a << endl;
                                cout << "B ranking " << b << endl;
                                cout << "C ranking " << c << endl;
                                cout << "D ranking " << d << endl;
                                cout << "E ranking " << e << endl;
                                thu = 1;
                            }
                        }
    if (thu == 0)
        cout << "No answer!" << endl;
    return 0;
}