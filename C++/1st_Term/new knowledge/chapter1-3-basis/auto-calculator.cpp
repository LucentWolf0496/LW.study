// It is an auto-calculator for grocery shopping.
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    float applePrice = 3.5;
    float bananaPrice = 4.2;
    float appleWeight = 0.0;
    float bananaWeight = 0.0;
    float total =0.0;
    cout << "Please enter the weight of your apples (kg): ";
    cin >> appleWeight;
    cout << "Please enter the weight of your bananas (kg): ";
    cin >> bananaWeight;
    total = applePrice * appleWeight + bananaPrice * bananaWeight;
    cout << "You should pay me " << total << " Yuan." << endl;
    return 0;
}