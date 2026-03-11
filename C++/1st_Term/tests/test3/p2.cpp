#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

int main(){
    double a;
    vector<double> list;
    while(cin >> a){
        list.push_back(a);
    }
    double x = 0 , y = 0;
    for (int i = 0 ; i < list.size() ; i += 2){
        x += list[i];
    }
    for (int i = 1 ; i < list.size() ; i += 2){
        y += list[i];
    }
    double result = sqrt(x * x + y * y);
    cout << fixed << setprecision(4) << result << endl;
    return 0;
}