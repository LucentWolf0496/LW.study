//example 2
#include <iostream>
using namespace std;

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int A = 0;
    int B = 0;
    int C = 0;
    int D = 0;
    int x = 0;
    int y = 0;
    a = 1; b = 0; c = 0; d = 0;//in the optimized version, this Loop is simplized into "for" of "best"
                               //use "for" to simplize the code
                               //then the way to check the expert turns into checking the number of "best"
    A = (b == 1);
    B = (d == 1);
    C = (c == 0);
    D = (d == 0);
    x = (A == 1) + (B == 1) + (C == 1) + (D == 1);
    if (x == 1)
    {
        y = 1;
        cout << "1 is the best" << endl;
        if (A == 1)
            cout << "A is right" << endl;
        else if (B == 1)
            cout << "B is right" << endl;
        else if (C == 1)
            cout << "C is right" << endl;
        else if (D == 1)
            cout << "D is right" << endl;
    }
    a = 0; b = 1; c = 0; d = 0;
    A = (b == 1);
    B = (d == 1);
    C = (c == 0);
    D = (d == 0);
    x = (A == 1) + (B == 1) + (C == 1) + (D == 1);
    if (x == 1)
    {
        y = 1;
        cout << "2 is the best" << endl;
        if (A == 1)
            cout << "A is right" << endl;
        else if (B == 1)
            cout << "B is right" << endl;
        else if (C == 1)
            cout << "C is right" << endl;
        else if (D == 1)
            cout << "D is right" << endl;
    }
    a = 0; b = 0; c = 1; d = 0;
    A = (b == 1);
    B = (d == 1);
    C = (c == 0);
    D = (d == 0);
    x = (A == 1) + (B == 1) + (C == 1) + (D == 1);
    if (x == 1)
    {
        y = 1;
        cout << "3 is the best" << endl;
        if (A == 1)
            cout << "A is right" << endl;
        else if (B == 1)
            cout << "B is right" << endl;
        else if (C == 1)
            cout << "C is right" << endl;
        else if (D == 1)
            cout << "D is right" << endl;
    }
    a = 0; b = 0; c = 0; d = 1;
    A = (b == 1);
    B = (d == 1);
    C = (c == 0);
    D = (d == 0);
    x = (A == 1) + (B == 1) + (C == 1) + (D == 1);
    if (x == 1)
    {
        y = 1;
        cout << "4 is the best" << endl;
        if (A == 1)
            cout << "A is right" << endl;
        else if (B == 1)
            cout << "B is right" << endl;
        else if (C == 1)
            cout << "C is right" << endl;
        else if (D == 1)
            cout << "D is right" << endl;
    }
    if (y == 0)
        cout << "No answer." << endl;
    return 0;
}