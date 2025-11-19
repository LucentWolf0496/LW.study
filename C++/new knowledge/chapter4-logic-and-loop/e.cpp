//calculation of e
#include <iostream>
using namespace std;

int main()
{
    double c = 1.0;
    double e = 1.0;
    int k = 1;
    do 
    {
        c = 1.0;
        for (int i = 1; i <= k; i++)
        {
            c = c / i;
        }
        k++;
        e = e + c;
    }while (c >= 1e-10);
    cout << e << endl;
    return 0;
}