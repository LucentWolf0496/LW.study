#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    for (int i = 0 ; i < n ; i ++){
        string num;
        cin >> num;
        stringstream ss(num);
        char x;
        int count = 0;
        while(ss >> x){
            if (!(x >= '0' && x <= '9') && !(x >= 'A' && x <= 'Z'))
                num[count] = ' ';
            count ++;
        }
        stringstream ss1(num);
        char y;
        vector<char> num1;
        while(ss1 >> y){
            num1.push_back(y);
        }
        for (int j = 0 ; j < 7 ; j ++){
            if (!(num1[j] >= '0' && num1[j] <= '9')){// 区分字符与数字，字符打单引号，数字不打
                if (num1[j] == 'A' || num1[j] == 'B' || num1[j] == 'C')
                    num1[j] = '2';
                else if (num1[j] == 'D' || num1[j] == 'E' || num1[j] == 'F')
                    num1[j] = '3';
                else if (num1[j] == 'G' || num1[j] == 'H' || num1[j] == 'I')
                    num1[j] = '4';
                else if (num1[j] == 'J' || num1[j] == 'K' || num1[j] == 'L')
                    num1[j] = '5';
                else if (num1[j] == 'M' || num1[j] == 'N' || num1[j] == 'O')
                    num1[j] = '6';
                else if (num1[j] == 'P' || num1[j] == 'R' || num1[j] == 'S')
                    num1[j] = '7';
                else if (num1[j] == 'T' || num1[j] == 'U' || num1[j] == 'V')
                    num1[j] = '8';
                else if (num1[j] == 'W' || num1[j] == 'X' || num1[j] == 'Y')
                    num1[j] = '9';
            }
        }
        for (int j = 0 ; j < 3 ; j ++){
            cout << num1[j];
        }
        cout << "-";
        for (int j = 3 ; j < 7 ; j ++){
            cout << num1[j];
        }
        cout << endl;
    }
    return 0;
}