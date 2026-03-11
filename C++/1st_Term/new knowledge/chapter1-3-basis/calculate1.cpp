// It is a demo produced by a beginner who dares to challenge the C++ Language.
// I guess that he will laugh at himself in the future when reading this code.
// However, being a beginner is always happy and interesting,although in face of a series of difficulties.
// Come on!
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    cout << 1+1/(1+1/(1+1/5.0)) << ","
         << sqrt(pow(3,2)+pow(4,2)) << ","
         << sqrt((1-cos(3.1415926/3))/2) << ","
         << pow(sin(3.1415926/4),2)+sin(3.1415926/4)*cos(3.1415926/4)-pow(cos(3.1415926/4),2) << ","
         << 2*sqrt(5)*(sqrt(6)+sqrt(3))/(6+3) << ","
         << ((log(5))*(log(3))-log(2))/sin(3.1415926/3) << ",How struggling I am! I am just a cat..."
         << endl;
    return 0;
}