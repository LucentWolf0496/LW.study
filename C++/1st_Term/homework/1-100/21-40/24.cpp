#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    int arr[n - 1];
    for (int i = 0 ; i <= n - 1 ; i ++)
    {
        int temp = 0;
        cin >> temp;
        arr[i] = temp;
    }
    for (int i = 0 ; i <= n - 1 - i ; i ++)
    {
        int temp = 0;
        temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
    cout << arr[0];
    for (int i = 1 ; i <= n - 1 ; i ++)
    {
        cout << " " << arr[i];
    }
    cout << endl;
    return 0;
}