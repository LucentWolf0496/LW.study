//example 4
#include <iostream>
using namespace std;

int main()
{
    int dt = 0, hz = 0, py = 0, t = 0;
    int A = 0, B = 0, C = 0, D = 0;
    int thu = 0;
    for (dt = 1; dt <= 4; dt++)
        for (hz = 1; hz <= 4; hz++)
            for (py = 1; py <= 4; py++)
                for (t = 1; t <= 4; t++)
                    if (dt != hz && dt != py && dt !=t && hz != py && hz != t && py != t)
                    {
                        A = (dt == 1) + (hz == 4) + (py == 3);
                        B = (hz == 1) + (dt == 4) + (py == 2) + (t == 3);
                        C = (hz == 4) + (dt == 3);
                        D = (py == 1) + (t == 4) + (hz == 2) + (dt == 3);
                        if (A == 1 && B == 1 && C == 1 && D == 1)
                        {
                            thu = 1;
                            cout << "dt ranking " << dt << endl;
                            cout << "hz ranking " << hz << endl;
                            cout << "py ranking " << py << endl;
                            cout << "t ranking " << t << endl;
                        }
                    }
    if (thu == 0)
        cout << "No answer!" << endl;
    return 0;
}