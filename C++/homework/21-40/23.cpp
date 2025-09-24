#include <iostream>
using namespace std;

int main()
{
    int m = 0;
    int n = 0;
    cin >> m >> n;
    int arr1[m];
    int arr2[n];
    for (int i = 0 ; i <= m - 1 ; i ++)
    {
        int temp = 0;
        cin >> temp;
        arr1[i] = temp;
    }
    for (int i = m - n ; i <= m - 1 ; i ++)
    {
        int p = 0;
        p = arr1[i];
        arr2[i - m + n] = p;
        arr1[i] = 0;
    }
    for (int i = 0 ; i <= m - n - 1 ; i ++)
    {
        arr1[m - i - 1] = arr1 [m - n - i - 1];
    }
    for (int i = 0 ; i <= n - 1 ; i ++)
    {
        arr1[i] = arr2[i];
    }
    cout << arr1[0];
    for (int i = 1 ; i <= m - 1 ; i ++)
    {
        cout << " " << arr1[i];
    }
    cout << endl;
}