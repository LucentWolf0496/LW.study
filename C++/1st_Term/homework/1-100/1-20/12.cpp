#include <iostream>
#include <cmath>
using namespace std;

int main() 
{
    int n = 0;
    cin >> n;
    
    for (int i = 1; i <= n; i++)
    {
        cout << "$";
        int j = 1, k = 1;
        
        if (i != (n + 1) / 2)
        {
            do
            {
                cout << " ";
                j++;
            }
            while (j <= abs(((n + 1) / 2) - i));
            
            do
            {
                cout << "*";
                k++;
            }
            while (j > abs(((n + 1) / 2) - i) && k <= n - 2 * abs(((n + 1) / 2) - i));
            
            cout << "" << endl;
        }
        else if (i == (n + 1) / 2)
        {
            do
            {
                cout << "*";
                k++;
            }
            while (k <= n);

            cout << "" << endl;
        }
    }
    
    return 0;
}