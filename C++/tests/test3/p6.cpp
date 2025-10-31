#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    cin.ignore();
    vector<string> list;
    for (int i = 0 ; i < n ; i ++){
        string temp;
        getline(cin , temp);
        list.push_back(temp);
    }
    for (int i = 0 ; i < n ; i ++){
        bool check = true;
        if ((list[i][0] >= 'a' && list[i][0] <= 'z') || (list[i][0] >= 'A' && list[i][0] <= 'Z') || (list[i][0] == '_')){
            for (int j = 1 ; j < list[i].size() ; j ++){
                if (!((list[i][j] >= 'a' && list[i][j] <= 'z') || (list[i][j] >= 'A' && list[i][j] <= 'Z') || (list[i][j] == '_') || (list[i][j] >= '0' && list[i][j] <= '9'))){
                    check = false;
                    break;
                }
            }
        }
        else
            check = false;
        cout << check << endl;
    }
    return 0;
}