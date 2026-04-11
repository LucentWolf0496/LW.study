#include <iostream>
#include <set>
#include <string>
using namespace std;

multiset<int> list;
set<int> history;

int main(){
    int n = 0;
    cin >> n;
    for (int i = 0 ; i < n ; i ++){
        string x;
        int y;
        cin >> x >> y;
        if (x == "add"){
            history.insert(y);
            list.insert(y);
            cout << list.count(y) << endl;
        }
        else if (x == "del"){
            cout << list.erase(y) << endl;
        }
        else{
            if (history.count(y)){
                cout << "1 " << list.count(y) << endl;
            }
            else{
                cout << "0 0" << endl;
            }
        }
    }
}