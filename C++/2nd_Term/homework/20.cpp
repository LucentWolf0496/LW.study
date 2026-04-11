#include <iostream>
using namespace std;

class MyCin{
private:
    bool check;
public:
    MyCin():check(true){  }
    MyCin & operator>>(int & x) {
        if (check){
            cin >> x;
            if (x == -1) check = false;
        }
        return *this;
    }
    operator bool() const { return check; }
};

int main(){
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}