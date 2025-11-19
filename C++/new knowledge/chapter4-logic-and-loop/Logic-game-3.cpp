//Eating ability accessment
#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
    int A, B, C;
    int x = 0;

    for (int A = 0; A <= 2; A++)
        for (int B = 0; B <= 2; B++)
            for (int C = 0; C <= 2; C++)
            {
                a= (B > A) + (C == A);
                b= (A > B) + (A > C);
                c= (C > B) + (B > A);
                if (a == 2)
                {
                    if (b == 1 && c == 0)
                    {
                        if (A < B && B < C)
                            cout << "C" << " > " << "B" << " > " << "A" << endl;
                            x = 1;
                    }
                    if (b == 0 && c == 1)
                    {
                        if (A < C && C < B)
                            cout << "B" << " > " << "C" << " > " << "A" << endl;
                            x = 1;                        
                    }
                }
                if (a == 1)
                {
                    if (b == 2 && c == 0)
                    {
                        if (B < A && A < C)
                            cout << "C" << " > " << "A" << " > " << "B" << endl;
                            x = 1;
                    }
                    if (b == 0 && c == 2)
                    {
                        if (C < A && A < B)
                            cout << "B" << " > " << "A" << " > " << "C" << endl;
                            x = 1;
                    }
                }
                if (a == 0)
                {
                    if (b == 2 && c == 1)
                    {
                        if (B < C && C < A)
                            cout << "A" << " > " << "C" << " > " << "B" << endl;
                            x = 1;
                    }
                    if (b == 1 && c == 2)
                    {
                        if (C < B && B < A)
                            cout << "A" << " > " << "B" << " > " << "C" << endl;
                            x = 1;
                    }
                }
            }
    if (x == 0)
        cout << "No answer." << endl;
    return 0;
}
