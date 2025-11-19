//test the rules of calculating,,,
//because of the "int",the numbers are restircted to integers!
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int a = 0 , b = 0 , c = 0;
    a = 3.1415926;
    b = a;
    c = sin(a);
    a = pow(c+b*(log(b)),2);
    b = b + 1;
    cout << a << " " << b << " " << c << "  AAAAAAAAdfmsdningoAAAAAAA" << endl;
    return 0;
}