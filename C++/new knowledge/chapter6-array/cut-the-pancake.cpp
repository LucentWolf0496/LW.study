#include <iostream>
using namespace std;

int main()
{
    int p[100];
    p[0] = 1;
    for (int i = 1 ; i <= 100 ; i ++)
    {
        p[i] = p[i - 1] + i;
    }
    int pancake = p[100];
    cout << pancake << endl;
    return 0;
}