#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    struct code{
        string name;
        string password;
        string email;
    };
    vector<code> list;
    string myemail;
    cin >> myemail;
    int n = 0;
    cin >> n;
    for (int i = 0 ; i < n ; i ++){
        string a , b , c;
        cin >> a >> b >> c;
        list.push_back({a , b , c});
    }
    int sum = list.size();
    bool check = true;
    for (int i = 0 ; i < sum ; i ++){
        if (list[i].email == myemail){
            check = false;
            for (int j = 0 ; j < list[i].password.size() ; j ++){
                if (list[i].password[j] >= 'A' && list[i].password[j] <= 'Z')
                     list[i].password[j] = list[i].password[j] - 'A' + 'a';
                else if (list[i].password[j] >= 'a' && list[i].password[j] <= 'z')
                     list[i].password[j] = list[i].password[j] - 'a' + 'A';
            }
            cout << list[i].name << " " << list[i].password << endl;
        }
    }
    if (check)
        cout << "empty" << endl;
    return 0;
}