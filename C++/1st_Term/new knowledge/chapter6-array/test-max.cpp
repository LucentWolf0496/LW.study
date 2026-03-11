// getting to konw the concept "array"
// the initial version of "array" is limited and is possibly wrong??!
// after getting to know the basic concept, please learn the upgraded "vector" version!
#include <iostream>
using namespace std;

int main()
{
    int a[6];
    int i = 0;
    int max = 0;
    int num = 0;
    for (int j = 0 ; j <= 5 ; j ++)
    {
        int t = 0;
        cin >> t;
        a[j] = t;
    }
    for (int *p = a ; p < a + 5 ; p ++)
    {
        if (max <= *p)
        {
            max = *p;
            i = p - a + 1;
        }
    }
    cout << "max=" << max << " , " << "its number is " << i << endl;
}