#include <iostream>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    for (int x = 0 ; x < n ; x ++){
        int a = 0 , b = 0;
        cin >> a >> b;
        if (a >= 0 && a <= 23 && b >= 0 && b <= 59){
            if ((a >= 6 && a <= 22) || (a == 23 && b == 0))
                cout << "Open." << endl;
            else
                cout << "Closed." << endl;
        }
        else{
            cout << "Invalid input!" << endl;
        }
    }
}