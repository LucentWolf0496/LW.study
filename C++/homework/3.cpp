#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double x = 0.0 , a = 0.0 , e = 0.0;
    cin >> x >> a >> e;
    int n = 0;
    int i = 0;
    double t = abs(x / pow(a , n));
    while (t >= e)
    {
        n ++;
        t = abs(x / pow(a , n));
    }
    cout << n - 1 << endl;
    return 0;
}