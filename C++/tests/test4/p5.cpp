#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    for (int j = 0 ; j < n ; j ++){
        string s;
        cin >> s;
        bool check1 = false;
        for (int i = 0 ; i < s.size() ; i ++){
            if (s[i] == ','){
                s[i] = ' ';
                check1 = true;
            }
        }
        if (check1){
            stringstream ss(s);
            string temp;
            while(ss >> temp){
                s = temp;
            }
        }
        vector<string> items;
        for (int i = 0 ; i < s.size() ; i ++){
            if (s[i] == '*' || s[i] == '+'){
                s[i] = ' ';
            }
        }
        stringstream ss(s);
        string temp;
        while(ss >> temp){
            items.push_back(temp);
        }
        bool x1 = false , x2 = false , x3 = false , x4 = false , x5 = false , x6 = false;
        for (int i = 0 ; i < items.size() ; i ++){
            if (items[i] == "char")
                x1 = true;
            else if (items[i] == "bool")
                x2 = true;
            else if (items[i] == "int")
                x3 = true;
            else if (items[i] == "longlong")
                x4 = true;
            else if (items[i] == "float")
                x5 = true;
            else if (items[i] == "double")
                x6 = true;
        }
        if (x1 && items.size() == 1)
            cout << "char" << endl;
        else if (x2 && items.size() == 1)
            cout << "bool" << endl;
        else{
            if (x6)
                cout << "double" << endl;
            else if (x5)
                cout << "float" << endl;
            else if (x4)
                cout << "longlong" << endl;
            else
                cout << "int" << endl;
        }
    }
    return 0;
}