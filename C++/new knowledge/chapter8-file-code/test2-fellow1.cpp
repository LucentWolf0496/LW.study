#include <iostream>
#include <cmath>
using namespace std;

int main(){
    cout << sin(20.0/180*3.1415926) +
            cos(20.0/180*3.1415926) -
            cos(10.0/180*3.1415926) /
            tan(10.0/180*3.1415926)
         << endl;
    return 0;
}
